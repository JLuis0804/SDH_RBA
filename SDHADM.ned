
package inet.node.sdh;

//
// SDH Add-Drop Multiplexer (ADM).
// Capaz de insertar tráfico PDH en una trama SDH y extraer tráfico para entregarlo localmente o reenviarlo.
//
simple SDHADM
{
    parameters:
        int stmLevel = default(1);             // STM-n level (1, 4, 16...)
        int numTributaries = default(1);       // Número de tributarios PDH
        bool allowMixedInsertion = default(false);        
        @display("i=block/routing");
        @class(SDHADM);
    gates:
        input pdhIn[numTributaries];
        output pdhOut[numTributaries];
        input lineIn[];  // Entradas desde otros ADM o LTE
        output lineOut[]; // Salidas hacia otros ADM o LTE
}

