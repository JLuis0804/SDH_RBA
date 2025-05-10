#ifndef __INET_SDHADM_H
#define __INET_SDHADM_H

#include <omnetpp.h>
#include <queue>
#include "SDHMessages_m.h"

namespace inet {

class SDHADM : public omnetpp::cSimpleModule
{
  protected:
    int numTributaries = 0;  // Number of pdhIn/pdhOut tributaries
    int stmLevel = 1;        // Level of STM (1, 4, 16...), used when regenerating frames
    bool allowMixedInsertion = false; // Allows both inserting PDH data into STM frames and generating new STM frames
    std::vector<std::queue<omnetpp::cPacket*>> tributaryBuffers;
    cMessage *frameTimer = nullptr;
    simsignal_t stmReenviadaSignal;
    simsignal_t pdhRecibidoSignal;
    simsignal_t pdhTransmitidoSignal;

    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage *msg) override;
    virtual void finish() override;
};

} // namespace inet

#endif
