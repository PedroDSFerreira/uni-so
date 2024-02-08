/*
 *  \author Carlos Ferreira (108822) / Daniel Emídio (108986)
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    uint32_t pctGetLifetime(uint32_t pid)
    {
        soProbe(305, "%s(%u)\n", __func__, pid);
        require(pid > 0, "a valid process ID must be greater than zero");

        // look for the node with right pid
        for (PctNode *current = pctHead; current != NULL; current = current->next) {
            if (current->pcb.pid == pid) {
                return current->pcb.lifetime;
            }
        }

        // if the pid does not exist, throw an exception
        throw Exception(EINVAL, __func__);
    }

// ================================================================================== //

    AddressSpaceProfile *pctGetAddressSpaceProfile(uint32_t pid)
    {
        soProbe(306, "%s(%u)\n", __func__, pid);

        require(pid > 0, "a valid process ID must be greater than zero");

        for (PctNode *aux = pctHead; aux != NULL; aux = aux->next) {
            if (aux->pcb.pid == pid) {
                return &aux->pcb.memProfile;
            }
        }

        // if the pid does not exist, throw an exception
        throw Exception(EINVAL, __func__);
    }

// ================================================================================== //

    AddressSpaceMapping *pctGetAddressSpaceMapping(uint32_t pid)
    {
        soProbe(307, "%s(%u)\n", __func__, pid);
        require(pid > 0, "a valid process ID must be greater than zero");

        for (PctNode *aux = pctHead; aux != NULL; aux = aux->next) {
            if (aux->pcb.pid == pid) {
                return &aux->pcb.memMapping;
            }
        }

        // if the pid does not exist, throw an exception
        throw Exception(EINVAL, __func__);
    }

// ================================================================================== //

    const char *pctGetStateAsString(uint32_t pid)
    {
        soProbe(308, "%s(%u)\n", __func__, pid);
        require(pid > 0, "a valid process ID must be greater than zero");

        // look for the node with right pid
        for (PctNode *current = pctHead; current != NULL; current = current->next) {
            if (current->pcb.pid == pid) {
                switch (current->pcb.state) {
                case ProcessState::NEW:
                    return "NEW";

                case ProcessState::ACTIVE:
                    return "ACTIVE";

                case ProcessState::SWAPPED:
                    return "SWAPPED";

                case ProcessState::FINISHED:
                    return "FINISHED";

                case ProcessState::DISCARDED:
                    return "DISCARDED";

                default:
                    throw Exception(EINVAL, __func__);
                }
            }
        }

        // if the pid does not exist, throw an exception
        throw Exception(EINVAL, __func__);
    }

// ================================================================================== //

} // end of namespace group
