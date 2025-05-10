package inet.node.sdh;

//
// SDH Line Terminating Equipment (LTE).
// Inserts and extracts PDH traffic from STM-n SDH frames.
//
simple SDHLTE
{
    parameters:
        int stmLevel = default(1);             // STM-n level (1, 4, 16...)
        int numTributaries = default(1);       // Number of tributaries supported
        bool useProtection = default(false);  // Enable dual output
        double protectionSwitchTime @unit(s) = default(-1s);  // -1 desactiva
        
        @signal[stmWorkingSent];
        @signal[stmProtectionSent];
        @signal[stmWorkingReceived];
        @signal[stmProtectionReceived];
        @signal[loadSTM];

       
        
        @statistic[stmWorkingSent](title="STM sent on working line"; source=stmWorkingSent; record=vector,last);
        @statistic[stmProtectionSent](title="STM sent on protection line"; source=stmProtectionSent; record=vector,last);
        @statistic[stmWorkingReceived](title="STM received on working line"; source=stmWorkingReceived; record=vector,last);
        @statistic[stmProtectionReceived](title="STM received on protection line"; source=stmProtectionReceived; record=vector,last);
       	@statistic[loadSTM](record=vector; title="load STM");

        
        @display("i=block/tx");
    gates:
    	input pdhIn[] @gatesize(numTributaries);
    	output pdhOut[] @gatesize(numTributaries);   	
        input lineIn[];
        output lineOut[];
}
