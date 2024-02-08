/*
 *  \author Carlos Ferreira (108822)
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    /*
     * \brief Init the module's internal data structure
     */
    void simInit(uint32_t mSize, uint32_t osSize, uint32_t cSize, AllocationPolicy policy)
    {
        const char *pas = policy == FirstFit ? "FirstFit" : policy == BuddySystem ? "BuddySystem" : "Unkown";
        soProbe(101, "%s(%#x, %#x, %#x, %s)\n", __func__, mSize, osSize, cSize, pas);

        // init the sim data structures and support variables
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

        // init all the other modules
        pctInit();
        feqInit();
        swpInit();
        memInit(mSize, osSize, cSize, policy);
    }

// ================================================================================== //

} // end of namespace group
