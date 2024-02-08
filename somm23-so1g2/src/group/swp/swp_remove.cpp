/*
 *  \author ...
 */

#include "somm23.h"

namespace group
{

    // ================================================================================== //

    void swpRemove(uint32_t idx)
    {
        soProbe(406, "%s(%u)\n", __func__, idx);

        // Remove the entry at the given position
        if (swpHead == NULL) {
            // Empty list, nothing to remove
            return;
        }

        if (idx == 0) {
            SwpNode *nodeToRemove = swpHead;
            swpHead = swpHead->next;
            free(nodeToRemove);

            // Update swpTail if the list becomes empty
            if (swpHead == NULL) {
                swpTail = NULL;
            }
            return;
        }

        uint32_t counter = 0;
        SwpNode *current = swpHead;
        while (current != NULL && counter < idx - 1) {
            current = current->next;
            counter++;
        }

        if (current == NULL || current->next == NULL) {
            // Index is out of bounds
            return;
        }

        SwpNode *nodeToRemove = current->next;
        if (nodeToRemove == swpTail) {
            // The index corresponds to the tail
            swpTail = current;
            current->next = NULL;
        } else {
            // The index is in the middle of the list
            current->next = nodeToRemove->next;
        }

        free(nodeToRemove);
    }

    // ================================================================================== //

} // end of namespace group
