package inet.node.sdh.p2pNetworkExtended;

import inet.node.sdh.SDHLTE;
import inet.node.sdh.PDHSource;
import inet.node.sdh.PDHSink;

//
// Bidirectional SDH network: each LTE has a source and a sink connected to it.
//
network p2pNetworkExtended
{
    types:
        channel FiberLine extends ned.DatarateChannel {
            parameters:
                datarate = default(155.52Mbps);
                delay = 2us;
                @display("m=arrow,ls=blue,2");
        }

    submodules:
        sourceA1: PDHSource {
            @display("p=100,75");
        }
        sourceA2: PDHSource {
            @display("p=100,150");
        }
        

        sinkA1: PDHSink {
            @display("p=100,250");
        }
        sinkA2: PDHSink {
            @display("p=100,325");
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

        sourceB1: PDHSource {
            @display("p=750,75");
        }
        sourceB2: PDHSource {
            @display("p=750,150");
        }

        sinkB1: PDHSink {
            @display("p=750,250");
        }
        sinkB2: PDHSink {
            @display("p=750,325");
        }

    connections allowunconnected:            
        sourceA1.out --> lteA.pdhIn++;
        lteA.lineOut++ --> FiberLine --> lteB.lineIn++;  // Línea operativa
        lteA.lineOut++ --> FiberLine --> lteB.lineIn++;  // Línea de protección
        lteB.pdhOut++ --> sinkB1.in;
        sourceA2.out --> lteA.pdhIn++;
        lteA.lineOut++ --> FiberLine --> lteB.lineIn++;  // Línea operativa
        lteA.lineOut++ --> FiberLine --> lteB.lineIn++;  // Línea de protección
        lteB.pdhOut++ --> sinkB2.in;
        
        sourceB1.out --> lteB.pdhIn++;
        lteB.lineOut++ --> FiberLine --> lteA.lineIn++;  // Línea operativa inversa
        lteB.lineOut++ --> FiberLine --> lteA.lineIn++;  // Línea de protección inversa
        lteA.pdhOut++ --> sinkA1.in; 
        sourceB2.out --> lteB.pdhIn++;
        lteB.lineOut++ --> FiberLine --> lteA.lineIn++;  // Línea operativa inversa
        lteB.lineOut++ --> FiberLine --> lteA.lineIn++;  // Línea de protección inversa
        lteA.pdhOut++ --> sinkA2.in; 
        
}
