#include "SDHDCS.h"

namespace inet {

Define_Module(SDHDCS);

/**
 * Initializes the DCS module (no internal state needed).
 */
void SDHDCS::initialize() {
    // Nothing to initialize for now
}

/**
 * Handles incoming SDH frames and transparently forwards them.
 * Logs VC info for debugging purposes.
 */
void SDHDCS::handleMessage(cMessage *msg) {
    if (msg->arrivedOn("lineIn")) {
        auto *frame = check_and_cast<SDHFrame *>(msg);

        // Optional: Inspect and log VCs in the frame
        for (int i = 0; i < frame->getVcArrayArraySize(); ++i) {
            SDHVirtualContainer vcCopy = frame->getVcArray(i);
            EV_INFO << "DCS: forwarding VC " << i
                    << " (tributaryIndex=" << vcCopy.getTributaryIndex()
                    << ", VCType=" << vcCopy.getVcType() << ")\n";
        }

        // Forward the frame
        send(frame, "lineOut");
    }
    else {
        delete msg;
    }
}

} // namespace inet
