#include "SDHLTE.h"

namespace inet {

Define_Module(SDHLTE);

/**
 * Initializes the SDHLTE module and schedules the first STM frame transmission.
 */
void SDHLTE::initialize() {
    stmLevel = par("stmLevel");
    useProtection = par("useProtection");
    numTributaries = gateSize("pdhIn");
    protectionSwitchTime = par("protectionSwitchTime");
    tributaryBuffers.resize(numTributaries);
    frameTimer = new cMessage("frameTimer");

    workingSignalTx = registerSignal("stmWorkingSent");
    protectionSignalTx = registerSignal("stmProtectionSent");
    workingSignalRx = registerSignal("stmWorkingReceived");
    protectionSignalRx = registerSignal("stmProtectionReceived");

    double bitrate = 155.52e6 * stmLevel;  // STM-n velocidad
    for (int i = 0; i < gateSize("lineOut"); ++i) {
        if (gate("lineOut", i)->isConnected()) {
            cChannel *chan = gate("lineOut", i)->getChannel();
            if (chan != nullptr && chan->hasPar("datarate")) {
                chan->par("datarate") = bitrate;
            }
        }
    }


    scheduleAt(simTime() + SimTime(125, SIMTIME_US), frameTimer);  // 8 kHz frame rate
}

/**
 * Handles incoming PDH, SDH, and self messages (for frame generation).
 */
void SDHLTE::handleMessage(cMessage *msg) {
    if (msg == frameTimer) {
        std::cout << "SDHLTE::handleMessage = frameTimer" << endl;

        bool sendFrame = false;
        for (int i = 0; i < numTributaries; ++i) {
            if (!tributaryBuffers[i].empty()) {
                sendFrame = true;
                break;
            }
        }

        if (sendFrame) {
            auto *frame = new SDHFrame("STM-Frame");
            frame->setStmLevel(stmLevel);

            int maxBytes = 2430 * stmLevel;
            int usedBytes = 0;

            auto *vc = new SDHVirtualContainer("VC4");
            vc->setVcType(VC4);
            vc->setTributaryIndex(0);  // asumimos un único VC por trama

            std::vector<cPacket*> acceptedPackets;

            for (int i = 0; i < numTributaries; ++i) {
                while (!tributaryBuffers[i].empty()) {
                    auto *pkt = tributaryBuffers[i].front();
                    int pktSize = pkt->getByteLength();

                    if (usedBytes + pktSize <= maxBytes) {
                        tributaryBuffers[i].pop();
                        usedBytes += pktSize;
                        acceptedPackets.push_back(pkt);
                        std::cout << "SDHLTE: accepted packet of " << pktSize << " bytes" << std::endl;
                    } else {
                        std::cout << "⚠️ SDHLTE: packet of size " << pktSize
                                  << " exceeds remaining frame capacity. Discarded." << std::endl;
                        delete pkt;
                        tributaryBuffers[i].pop();
                    }
                }
            }

            // Encapsular los paquetes en el array payloads[]
            vc->setPayloadsArraySize(acceptedPackets.size());
            for (size_t i = 0; i < acceptedPackets.size(); ++i) {
                vc->setPayloads(i, *acceptedPackets[i]);
                delete acceptedPackets[i];
            }

            // Insertar el VC4 en el SDHFrame
            frame->setVcArrayArraySize(1);
            frame->setVcArray(0, *vc);
            delete vc;

            // Color según carga
            double loadRatio = (double)usedBytes / maxBytes;

            bool useProtectionNow = useProtection && (protectionSwitchTime >= 0 && simTime() >= protectionSwitchTime);

            if (useProtectionNow && gateSize("lineOut") > 1) {
                int red = std::min(255, std::max(0, (int)(255 * loadRatio)));
                char redStr[64];
                sprintf(redStr, "bgb=rgb(%d,%d,%d)", 255, 255 - red, 255 - red);
                frame->setName(("STM used " + std::to_string(usedBytes) + "/" + std::to_string(maxBytes)).c_str());
                send(frame, "lineOut", 1);
                emit(protectionSignalTx, ++stmCountProtectionTx);
            } else {
                int blue = std::min(255, std::max(0, (int)(255 * loadRatio)));
                char displayStr[64];
                sprintf(displayStr, "bgb=rgb(%d,%d,%d)", 255 - blue, 255 - blue, 255);
                frame->setName(("STM used " + std::to_string(usedBytes) + "/" + std::to_string(maxBytes)).c_str());
                send(frame, "lineOut", 0);
                emit(workingSignalTx, ++stmCountWorkingTx);
            }

        }

        scheduleAt(simTime() + SimTime(125, SIMTIME_US), frameTimer);
    }
    else if (msg->arrivedOn("pdhIn")) {
        std::cout << "SDHLTE::handleMessage = pdhIn" << endl;
        int index = msg->getArrivalGate()->getIndex();
        if (index >= 0 && index < (int)tributaryBuffers.size()) {
            auto *pdhPacket = check_and_cast<cPacket*>(msg);
            tributaryBuffers[index].push(pdhPacket);
        } else {
            delete msg;
        }
    }
    else if (msg->arrivedOn("lineIn")) {
        std::cout << "SDHLTE::handleMessage = lineIn" << endl;
        int arrivalGate = msg->getArrivalGate()->getIndex();
        if (arrivalGate == 0) {
            emit(workingSignalRx, ++stmCountWorkingRx);
        } else {
            emit(protectionSignalRx, ++stmCountProtectionRx);
        }
        auto *frame = check_and_cast<SDHFrame*>(msg);

        for (int i = 0; i < frame->getVcArrayArraySize(); ++i) {
            SDHVirtualContainer vcCopy = frame->getVcArray(i);
            auto *vc = vcCopy.dup();
            int t = vc->getTributaryIndex();

            // 🔍 Solo si hay gate de salida
            int numPackets = vc->getPayloadsArraySize();
            if (numPackets > 0 && t >= 0 && t < gateSize("pdhOut") && gate("pdhOut", t)->isConnected()) {
                simtime_t totalFrameTime = SimTime(125, SIMTIME_US);
                simtime_t packetSpacing = totalFrameTime / numPackets;

                for (int j = 0; j < numPackets; ++j) {
                    cPacket *pdh = vc->getPayloads(j).dup();
                    simtime_t delay = j * packetSpacing;
                    sendDelayed(pdh, delay, "pdhOut", t);

                    EV << "Sent PDH packet " << pdh->getName()
                       << " from VC[" << i << "] to pdhOut[" << t << "] at t+" << delay << endl;
                }
            }
            delete vc;
        }

        delete frame;
    }
    else {
        delete msg;
    }
}

/**
 * Frees resources and deletes buffered messages on simulation end.
 */
void SDHLTE::finish() {
    cancelAndDelete(frameTimer);

    for (auto& queue : tributaryBuffers) {
        while (!queue.empty()) {
            delete queue.front();
            queue.pop();
        }
    }

    EV << "STM transmitidos por línea operativa: " << stmCountWorkingTx << endl;
    EV << "STM transmitidos por línea de protección: " << stmCountProtectionTx << endl;
    EV << "STM recibidos por línea operativa: " << stmCountWorkingRx << endl;
    EV << "STM recibidos por línea de protección: " << stmCountProtectionRx << endl;
}


} // namespace inet
