/*
 *  \author Carlos Ferreira (108822)
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    void simRun(uint32_t cnt)
    {
        soProbe(108, "%s(%u)\n", __func__, cnt);

        // run for a number of steps or until the reach cnt
        for (uint32_t i = 0; cnt == 0 || i < cnt; i++) {
            if (!simStep()) {
                break;
            }
        }
    }

// ================================================================================== //

} // end of namespace group
