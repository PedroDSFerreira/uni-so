/*
 *  \author ...
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    SwappedProcess *swpPeek(uint32_t idx)
    {
        soProbe(405, "%s(%u)\n", __func__, idx);

        // TODO: EXEPTIONS(quando n tem head e quando n tem esse idx) e o que fazer quando acha o idx (ns bem, um print?)
        // ciclo entre a list desde a head ate a tail de next em next ate chegar ao idx
        if (swpHead == NULL){
            // erro, lista vazia n dá peek ou dá return de NULL??
            return NULL;
        }

        SwpNode *current = swpHead;
        for (uint32_t counter = 0; current != NULL; current = current->next) {
            if (idx == counter) {
                return &current->process;
            }

            counter++;
        }

        return NULL;
    }

// ================================================================================== //

} // end of namespace group
