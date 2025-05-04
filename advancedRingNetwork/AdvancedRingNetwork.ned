
package inet.node.sdh.advancedRingNetwork;

import inet.node.sdh.SDHADM;
import inet.node.sdh.SDHLTE;
import inet.node.sdh.PDHSource;
import inet.node.sdh.PDHSink;

network AdvancedRingNetwork
{
    types:
        channel FiberLine extends ned.DatarateChannel
        {
            parameters:
                datarate = default(155.52Mbps);
                delay = 2us;
                @display("m=arrow,ls=blue,2");
        }

    submodules:
        adm1: SDHADM {
            parameters:
                @display("p=223,189");
        }
        adm2: SDHADM {
            parameters:
                @display("p=327,91");
        }
        adm3: SDHADM {
            parameters:
                @display("p=459,189");
        }
        adm4: SDHADM {
            parameters:
                @display("p=410,300");
        }
        adm5: SDHADM {
            @display("p=269,300");
        }

        // Fuente y destino conectados a LTEs
        source1: PDHSource {
            @display("p=79,161");
        }
        sink1: PDHSink {
            @display("p=145,103");
        }

        source31: PDHSource {
            @display("p=649,218");
        }
        source32: PDHSource {
            @display("p=649,150");
        }
        sink3: PDHSink {
            @display("p=600,77");
        }

        sink4: PDHSink {
            @display("p=533,314");
        }

    connections allowunconnected:

        // El anillo
        adm1.lineOut++ --> FiberLine --> adm2.lineIn++;
        adm2.lineOut++ --> FiberLine --> adm3.lineIn++;
        adm3.lineOut++ --> FiberLine --> adm4.lineIn++;
        adm4.lineOut++ --> FiberLine --> adm5.lineIn++;
        adm5.lineOut++ --> FiberLine --> adm1.lineIn++;

        // Sources y sinks conectados a LTEs o ADMs
        source1.out --> adm1.pdhIn++;
        adm1.pdhOut++ --> sink1.in;

        source31.out --> adm3.pdhIn++;
        source32.out --> adm3.pdhIn++;
        adm3.pdhOut++ --> sink3.in;

        adm4.pdhOut++ --> sink4.in;

}
