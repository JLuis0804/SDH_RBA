//package inet.node.sdh;

import inet.common.INETDefs;
import inet.common.packet.Packet;

cplusplus {{
#include "omnetpp.h"
#include "inet/common/packet/Packet.h"
}}

enum VCType {
    VC12 = 12;
    VC3 = 3;
    VC4 = 4;
}

class SDHVirtualContainer extends inet::Packet 
{
    VCType vcType;
    int tributaryIndex;
    cPacket payloads[];  
}


class SDHFrame extends cPacket
{
    int stmLevel;
    SDHVirtualContainer vcArray[];
    bool isProtection;
}
