
package inet.node.sdh;

//
// Simple PDH sink to count received packets.
//
simple PDHSink
{
    parameters:
        @display("i=block/sink");
    gates:
        input in;
}

