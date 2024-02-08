/*
 *  \author Carlos Ferreira (108822)
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    void simTerm() 
    {
        soProbe(102, "%s()\n", __func__);

        // term all the other modules
        pctTerm();
        feqTerm();
        swpTerm();
        memTerm();

        // term the sim module (reset to the initial state)
        stepCount = 0;
        simTime = 0;
        forthcomingTable.count = 0;

        for (uint32_t i = 0; i < MAX_PROCESSES; i++) {
            forthcomingTable.process[i].pid = -1;
            forthcomingTable.process[i].arrivalTime = NO_TIME;
            forthcomingTable.process[i].lifetime = -1;

            forthcomingTable.process[i].addressSpace.segmentCount = 0;
            for (uint32_t j = 0; j < MAX_BLOCKS; j++) {
                forthcomingTable.process[i].addressSpace.size[j] = -1;
            }
        }
    }

// ================================================================================== //

} // end of namespace group
