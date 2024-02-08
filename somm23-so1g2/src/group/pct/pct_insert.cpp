/*
 *  \author Daniel Emídio (108986)
 */

#include "somm23.h"
#include <stdint.h>

namespace group
{

// ================================================================================== //

    void pctInsert(uint32_t pid, uint32_t time, uint32_t lifetime, AddressSpaceProfile *profile)
    {
        soProbe(304, "%s(%d, %u, %u, %p)\n", __func__, pid, time, lifetime, profile);
        require(pid > 0, "a valid process ID must be greater than zero");
        require(time >= 0, "time must be >= 0");
        require(lifetime > 0, "lifetime must be > 0");
        require(profile != NULL, "profile must be a valid pointer to a AddressSpaceProfile");

        // create and populate the new node
        PctNode *new_node = (PctNode *)malloc(sizeof(PctNode));

        // throw ENOMEM exception if memory was not allocated
        if (new_node == NULL) {
            throw Exception(ENOMEM, __func__);
        }

        new_node->next = NULL;
        new_node->pcb.arrivalTime = time;
        new_node->pcb.lifetime = lifetime;
        new_node->pcb.pid = pid;
        new_node->pcb.state = ProcessState::NEW;
        new_node->pcb.activationTime = NO_TIME;
        new_node->pcb.finishTime = NO_TIME;
        new_node->pcb.memMapping.blockCount = 0;
        for (uint32_t i = 0; i < MAX_BLOCKS; i++) new_node->pcb.memMapping.address[i] = 0;
        new_node->pcb.memProfile.segmentCount = profile->segmentCount;
        for (uint32_t i = 0; i < MAX_BLOCKS; i++) new_node->pcb.memProfile.size[i] = profile->size[i];

        // check if the new node needs to be in the first position
        if (pctHead == NULL || pctHead->pcb.pid > pid) {
            // insert the node at the beginning
            new_node->next = pctHead;
            pctHead = new_node;
        } else {
            // throw EINVAL exception if there are 2 equal pids
            if (pctHead->pcb.pid == pid) {
                throw Exception(EINVAL, __func__);
            }

            // find the spot in the list for the new node
            PctNode *current = pctHead;
            while (current->next != NULL && current->next->pcb.pid < pid) {
                // throw EINVAL exception if there are 2 equal pids
                if (current->next->pcb.pid == pid) {
                    throw Exception(EINVAL, __func__);
                }

                current = current->next;
            }

            // insert the new node
            new_node->next = current->next;
            current->next = new_node;
        }
    }

// ================================================================================== //

} // end of namespace group
