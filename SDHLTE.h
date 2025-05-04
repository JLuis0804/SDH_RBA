#ifndef __INET_NODE_SDH_SDHLTE_H
#define __INET_NODE_SDH_SDHLTE_H

#include "omnetpp.h"
#include "inet/node/sdh/SDHMessages_m.h"
#include <queue>

using namespace omnetpp;
using namespace inet;

namespace inet {

/**
 * SDH Line Terminating Equipment (LTE) that multiplexes PDH into SDH frames
 * and demultiplexes them on reception.
 */
class SDHLTE : public cSimpleModule {
  private:
    int stmLevel;                            // STM-n level (1, 4, etc.)
    int numTributaries;                      // Number of tributary ports
    double protectionSwitchTime;
    bool useProtection;                      // Whether to send duplicate frames
    std::vector<std::queue<cPacket*>> tributaryBuffers;
    cMessage *frameTimer;                    // Triggers periodic frame generation

    int stmCountWorkingTx = 0;
    int stmCountProtectionTx = 0;
    int stmCountWorkingRx = 0;
    int stmCountProtectionRx = 0;

    simsignal_t workingSignalTx;
    simsignal_t protectionSignalTx;
    simsignal_t workingSignalRx;
    simsignal_t protectionSignalRx;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

} // namespace inet

#endif
