#include "PDHSink.h"
#include "inet/common/packet/Packet.h"
#include "SDHMessages_m.h"

namespace inet {

Define_Module(PDHSink);

/**
 * Initializes the module by setting the received packet counter to zero.
 */
void PDHSink::initialize() {
    count = 0;
    WATCH(count);  // Allows inspection in the OMNeT++ GUI
}

/**
 * Handles received packets.
 */
void PDHSink::handleMessage(cMessage *msg) {
    auto *pkt = check_and_cast<cPacket*>(msg);
    count++;

    EV << "PDHSink received packet: " << pkt->getName() << endl;
    delete pkt;
}


/**
 * Displays the final count at the end of the simulation.
 */
void PDHSink::finish() {
    EV << "PDHSink total packets received: " << count << endl;
}

} // namespace inet
