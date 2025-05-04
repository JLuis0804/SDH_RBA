#include "SDHADM.h"

namespace inet {

Define_Module(SDHADM);

void SDHADM::initialize() {
    numTributaries = gateSize("pdhIn");
    tributaryBuffers.resize(numTributaries);
    stmLevel = par("stmLevel");
    allowMixedInsertion = par("allowMixedInsertion");

    double bitrate = 155.52e6 * stmLevel;  // STM-n velocidad
    for (int i = 0; i < gateSize("lineOut"); ++i) {
        if (gate("lineOut", i)->isConnected()) {
            cChannel *chan = gate("lineOut", i)->getChannel();
            if (chan != nullptr && chan->hasPar("datarate")) {
                chan->par("datarate") = bitrate;
            }
        }
    }


    frameTimer = new cMessage("ADMFrameTimer");
    scheduleAt(simTime() + SimTime(125, SIMTIME_US), frameTimer);
}

void SDHADM::handleMessage(cMessage *msg) {
    if (msg == frameTimer) {
        int maxBytes = 2430 * stmLevel;
        int usedBytes = 0;

        auto *vc = new SDHVirtualContainer("VC4");
        vc->setVcType(VC4);
        vc->setTributaryIndex(0);

        std::vector<cPacket*> packets;
        for (int i = 0; i < numTributaries; ++i) {
            while (!tributaryBuffers[i].empty()) {
                auto *pkt = tributaryBuffers[i].front();
                int pktSize = pkt->getByteLength();

                if (usedBytes + pktSize <= maxBytes) {
                    tributaryBuffers[i].pop();
                    usedBytes += pktSize;
                    packets.push_back(pkt);
                } else {
                    delete pkt;
                    tributaryBuffers[i].pop();
                }
            }
        }

        if (!packets.empty()) {
            vc->setPayloadsArraySize(packets.size());
            for (size_t i = 0; i < packets.size(); ++i) {
                vc->setPayloads(i, *packets[i]);
                delete packets[i];
            }

            auto *frame = new SDHFrame("Generated STM");
            frame->setStmLevel(stmLevel);
            frame->setVcArrayArraySize(1);
            frame->setVcArray(0, *vc);
            delete vc;

            for (int i = 0; i < gateSize("lineOut"); ++i) {
                if (gate("lineOut", i)->isConnected()) {
                    send(frame->dup(), "lineOut", i);
                }
            }

            delete frame;
        } else {
            delete vc;
        }

        scheduleAt(simTime() + SimTime(125, SIMTIME_US), frameTimer);
    }

    else if (msg->arrivedOn("pdhIn")) {
        int index = msg->getArrivalGate()->getIndex();
        if (index >= 0 && index < (int)tributaryBuffers.size()) {
            auto *pdhPacket = check_and_cast<cPacket*>(msg);
            tributaryBuffers[index].push(pdhPacket);
        } else {
            delete msg;
        }
    }

    else if (msg->arrivedOn("lineIn")) {
        auto *frame = check_and_cast<SDHFrame*>(msg);
        std::vector<SDHVirtualContainer*> forwardVCs;

        // 1. Extraer los VCs si el tributary está conectado a un PDH
        for (int i = 0; i < frame->getVcArrayArraySize(); ++i) {
            SDHVirtualContainer vcCopy = frame->getVcArray(i);
            auto *vc = vcCopy.dup();
            int t = vc->getTributaryIndex();

            if (t >= 0 && t < gateSize("pdhOut") && gate("pdhOut", t)->isConnected()) {
                int numPackets = vc->getPayloadsArraySize();
                simtime_t totalFrameTime = SimTime(125, SIMTIME_US);
                simtime_t packetSpacing = totalFrameTime / numPackets;
                for (int j = 0; j < vc->getPayloadsArraySize(); ++j) {
                    auto *pdh = vc->getPayloads(j).dup();
                    simtime_t delay = j * packetSpacing;
                    sendDelayed(pdh, delay, "pdhOut", t);
                    EV << "Sent PDH packet " << pdh->getName()
                       << " from VC[" << i << "] to pdhOut[" << t << "] at t+" << delay << endl;

                }
                delete vc;
            } else {
                forwardVCs.push_back(vc);
            }
        }

        // 2. (opcional) insertar datos locales
        if (allowMixedInsertion) {
            int maxBytes = 2430 * stmLevel;
            int usedBytes = 0;
            auto *newVC = new SDHVirtualContainer("VC4");
            newVC->setVcType(VC4);
            newVC->setTributaryIndex(0);

            std::vector<cPacket*> insertedPackets;
            for (int i = 0; i < numTributaries; ++i) {
                while (!tributaryBuffers[i].empty()) {
                    auto *pkt = tributaryBuffers[i].front();
                    int pktSize = pkt->getByteLength();
                    if (usedBytes + pktSize <= maxBytes) {
                        tributaryBuffers[i].pop();
                        usedBytes += pktSize;
                        insertedPackets.push_back(pkt);
                    } else {
                        delete pkt;
                        tributaryBuffers[i].pop();
                    }
                }
            }

            if (!insertedPackets.empty()) {
                newVC->setPayloadsArraySize(insertedPackets.size());
                for (size_t i = 0; i < insertedPackets.size(); ++i) {
                    newVC->setPayloads(i, *insertedPackets[i]);
                    delete insertedPackets[i];
                }
                forwardVCs.push_back(newVC);
            } else {
                delete newVC;
            }
        }

        // 3. Reenviar si quedan VCs
        if (!forwardVCs.empty()) {
            auto *newFrame = new SDHFrame("Forwarded STM");
            newFrame->setStmLevel(frame->getStmLevel());
            newFrame->setVcArrayArraySize(forwardVCs.size());

            for (int i = 0; i < (int)forwardVCs.size(); ++i) {
                newFrame->setVcArray(i, *forwardVCs[i]);
                delete forwardVCs[i];
            }

            for (int i = 0; i < gateSize("lineOut"); ++i) {
                if (gate("lineOut", i)->isConnected()) {
                    send(newFrame->dup(), "lineOut", i);
                }
            }

            delete newFrame;
        }

        delete frame;
    }

    else {
        delete msg;
    }
}

void SDHADM::finish() {
    cancelAndDelete(frameTimer);
    for (auto& queue : tributaryBuffers) {
        while (!queue.empty()) {
            delete queue.front();
            queue.pop();
        }
    }
}

} // namespace inet
