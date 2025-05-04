package inet.node.sdh.p2pNetwork;

import inet.node.sdh.SDHLTE;
import inet.node.sdh.PDHSource;
import inet.node.sdh.PDHSink;

//
// Bidirectional SDH network: each LTE has a source and a sink connected to it.
//
network p2pNetwork
{
    types:
        channel FiberLine extends ned.DatarateChannel {
            parameters:
                datarate = default(155.52Mbps);
                delay = 2us;
                @display("m=arrow,ls=blue,2");
        }

    submodules:
        sourceA: PDHSource {
            @display("p=100,150");
        }

        sinkA: PDHSink {
            @display("p=100,250");
        }

        lteA: SDHLTE {
            parameters:
                stmLevel = default(1);
                numTributaries = default(1);
                useProtection = default(false);
                @display("p=300,200");
        }

        lteB: SDHLTE {
            parameters:
                stmLevel = default(1);
                numTributaries = default(1);
                useProtection = default(false);
                @display("p=500,200");
        }

        sourceB: PDHSource {
            @display("p=700,150");
        }

        sinkB: PDHSink {
            @display("p=700,250");
        }

    connections allowunconnected:            
        sourceA.out --> lteA.pdhIn++;
        lteA.lineOut++ --> FiberLine --> lteB.lineIn++;  // Línea operativa
        lteA.lineOut++ --> FiberLine --> lteB.lineIn++;  // Línea de protección
        lteB.pdhOut++ --> sinkB.in;
        
        sourceB.out --> lteB.pdhIn++;
        lteB.lineOut++ --> FiberLine --> lteA.lineIn++;  // Línea operativa inversa
        lteB.lineOut++ --> FiberLine --> lteA.lineIn++;  // Línea de protección inversa
        lteA.pdhOut++ --> sinkA.in; 
        
}
