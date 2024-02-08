/*
 *  \author Carlos Ferreira (108822)
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    void pctTerm()
    {
        soProbe(302, "%s()\n", __func__);

        // free all the nodes
        PctNode *current = pctHead;
        PctNode *next = NULL;

        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }

        pctHead = NULL;
    }

// ================================================================================== //

} // end of namespace group
