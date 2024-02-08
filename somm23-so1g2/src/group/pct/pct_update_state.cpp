/*
 *  \author Daniel Emídio (108987)
 */

#include "somm23.h"
#include <stdint.h>

namespace group
{

// ================================================================================== //

    void pctUpdateState(uint32_t pid, ProcessState state, uint32_t time = NO_TIME, AddressSpaceMapping *mapping = NULL)
    {
        soProbe(309, "%s(%d, %u, %u)\n", __func__, pid, state, time);
        require(pid > 0, "a valid process ID must be greater than zero");

        for (PctNode *current = pctHead; current != NULL; current = current->next) {
            if (current->pcb.pid == pid) {
                current->pcb.state = state;
                switch (state) {
                case ProcessState::ACTIVE:
                    current->pcb.activationTime = time;
                    current->pcb.memMapping = *mapping;
                    break;

                case ProcessState::FINISHED:
                    current->pcb.finishTime = time;
                    break;

                case ProcessState::DISCARDED:
                case ProcessState::SWAPPED:
                    break;

                default:
                    // invalid state
                    throw Exception(EINVAL, __func__);
                }

                return;
            }
        }

        // if the process is not found
        throw Exception(EINVAL, __func__);
    }

// ================================================================================== //

} // end of namespace group
