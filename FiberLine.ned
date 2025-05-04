
package inet.node.sdh;

channel FiberLine extends ned.DatarateChannel
{
    parameters:
        @class(DatarateChannel);
        datarate @unit(bps) = default(155.52Mbps); // STM-1 por defecto
        delay @unit(s) = default(0us);             // Latencia nula por defecto
        @display("m=arrow,ls=blue,2");
}
