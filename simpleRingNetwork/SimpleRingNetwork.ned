package inet.node.sdh.simpleRingNetwork;

import inet.node.sdh.SDHADM;
import inet.node.sdh.SDHLTE;
import inet.node.sdh.PDHSource;
import inet.node.sdh.PDHSink;

network SimpleRingNetwork
{
    types:
        channel FiberLine extends ned.DatarateChannel
        {
            parameters:
                datarate = default(155.52Mbps);
                delay = default(2us);
                @display("m=arrow,ls=blue,2");
        }

    submodules:
        adm1: SDHADM {
            @display("p=300,100");
        }
        adm2: SDHADM {
            @display("p=500,100");
        }
        adm3: SDHADM {
            @display("p=600,300");
        }
        adm4: SDHADM {
            @display("p=400,400");
        }
        adm5: SDHADM {
            @display("p=200,300");
        }

        source: PDHSource {
            @display("p=118,100");
        }

        sink: PDHSink {
            @display("p=743,300");
        }

    connections allowunconnected:
        // Anillo SDH
        adm1.lineOut++ --> FiberLine --> adm2.lineIn++;
        adm2.lineOut++ --> FiberLine --> adm3.lineIn++;
        adm3.lineOut++ --> FiberLine --> adm4.lineIn++;
        adm4.lineOut++ --> FiberLine --> adm5.lineIn++;
        adm5.lineOut++ --> FiberLine --> adm1.lineIn++;
       
        // Fuente y destino:
        source.out --> FiberLine --> adm1.pdhIn++;
        sink.in <-- FiberLine <-- adm3.pdhOut++;

}
