#ifndef __INET_NODE_SDH_PDHSOURCE_H
#define __INET_NODE_SDH_PDHSOURCE_H

#include "omnetpp.h"

using namespace omnetpp;

/**
 * Simple PDH source that periodically generates dummy packets to be
 * encapsulated into SDH virtual containers.
 */
namespace inet {

class PDHSource : public cSimpleModule {
  private:
    simtime_t packetInterval; // Packet interval
    int packetSize; // Packet size in Bytes
    int counter;
    cMessage *sendTimer;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

} // namespace inet

#endif
