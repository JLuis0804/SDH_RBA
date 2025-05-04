#include "PDHSource.h"
#include "inet/common/packet/Packet.h"

namespace inet {

Define_Module(PDHSource);

/**
 * Initializes the module: sets the interval and schedules the first packet generation.
 */
void PDHSource::initialize() {
    EV << "PDHSource initialized at " << getFullPath() << endl;
    packetInterval = par("packetInterval");
    packetSize = par("packetSize").intValue();;
    counter = 0;
    sendTimer = new cMessage("sendTimer");
    scheduleAt(simTime() + packetInterval, sendTimer);
}

/**
 * Handles the sendTimer message by generating and sending a new dummy Packet.
 */
void PDHSource::handleMessage(cMessage *msg) {
    if (msg == sendTimer) {
        char name[32];
        sprintf(name, "PDH-%d", counter++);
        auto *pdhPacket = new cPacket(name);
        pdhPacket->setByteLength(packetSize);
        send(pdhPacket, "out");
        scheduleAt(simTime() + packetInterval, sendTimer);
    } else {
        delete msg;
    }
}

/**
 * Clean-up: cancels and deletes the timer message.
 */
void PDHSource::finish() {
    cancelAndDelete(sendTimer);
}

} // namespace inet

