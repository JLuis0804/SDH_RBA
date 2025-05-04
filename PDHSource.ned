
package inet.node.sdh;

//
// Simple PDH traffic generator.
//
simple PDHSource
{
    parameters:
        double packetInterval @unit(s) = default(10us); // Interval between packets
        int packetSize = default(300); // Packet size in bytes
        @display("i=block/source");
        @class(PDHSource);
    gates:
        output out;
}


