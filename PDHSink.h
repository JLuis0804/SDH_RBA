#ifndef __INET_NODE_SDH_PDHSINK_H
#define __INET_NODE_SDH_PDHSINK_H

#include "omnetpp.h"

using namespace omnetpp;

namespace inet {

/**
 * Simple PDH sink that receives and counts incoming PDH packets.
 */
class PDHSink : public cSimpleModule {
  private:
    int count;  // Number of received packets

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

} // namespace inet

#endif
