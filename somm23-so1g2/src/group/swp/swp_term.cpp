/*
 *  \author ...
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

void swpTerm() {
    soProbe(402, "%s()\n", __func__);

    while (swpHead != NULL) {
        SwpNode *aux = swpHead->next;
        free(swpHead);
        swpHead = aux;
    }
}

// ================================================================================== //

} // end of namespace group
