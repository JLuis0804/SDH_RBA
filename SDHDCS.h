#ifndef __INET_NODE_SDH_SDHDCS_H
#define __INET_NODE_SDH_SDHDCS_H

#include "omnetpp.h"
#include "inet/node/sdh/SDHMessages_m.h"

using namespace omnetpp;
using namespace inet;

namespace inet {

/**
 * SDH Digital Cross-connect System (DCS) that transparently forwards
 * SDH frames, optionally inspecting their contents (VCs).
 */
class SDHDCS : public cSimpleModule {
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

} // namespace inet

#endif
