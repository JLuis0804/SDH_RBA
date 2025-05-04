
package inet.node.sdh;

//
// SDH Digital Cross-Connect System.
// Connects multiple SDH lines and may perform VC-level switching.
//
simple SDHDCS
{
    parameters:
        int stmLevel;             // STM-n level
        int numLines;             // Number of SDH lines (input/output pairs)
        bool useProtection = default(false);
        @display("i=block/cogwheel");
    gates:
        input lineIn[numLines];
        output lineOut[numLines];
}
