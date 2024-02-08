/*
 *  \author Daniel Emídio (108986)
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    bool simStep()
    {
        soProbe(107, "%s()\n", __func__);

        //  If the FEQ queue is empty, nothing should be done and the function must return false
        if (feqIsEmpty()) {
            return false;
        }

        // fetching an event from the FEQ module 
        FutureEvent event = feqPop();

        simTime = event.time;
        stepCount++;

        // the processing to be done depends on the event type
        if(event.type == FutureEventType::ARRIVAL) {
            ForthcomingProcess *newEvent = simGetProcess(event.pid);
            pctInsert(newEvent->pid, newEvent->arrivalTime, newEvent->lifetime, &newEvent->addressSpace);
            AddressSpaceMapping *p = memAlloc(newEvent->pid, &newEvent->addressSpace);

            if (p == IMPOSSIBLE_MAPPING) {
                pctUpdateState(newEvent->pid, ProcessState::DISCARDED);
            } else if (p == NO_MAPPING) {
                swpAdd(newEvent->pid, &newEvent->addressSpace);
                pctUpdateState(newEvent->pid, ProcessState::SWAPPED);
            } else {
                feqInsert(FutureEventType::TERMINATE, newEvent->lifetime + simTime, newEvent->pid);
                pctUpdateState(newEvent->pid, ProcessState::ACTIVE, simTime, p);
            }
        } else {
            AddressSpaceMapping *p = pctGetAddressSpaceMapping(event.pid);
            memFree(p);
            pctUpdateState(event.pid, ProcessState::FINISHED, event.time);
            int i = 0;
            while(true) {
                SwappedProcess *peek_ptr = swpPeek(i);
                if(peek_ptr == NULL){
                    break;
                }
                AddressSpaceProfile *asp = pctGetAddressSpaceProfile(peek_ptr->pid); 
                AddressSpaceMapping *ptr = memAlloc(peek_ptr->pid, asp);
                if (ptr == NULL) {
                    i++;
                } else {
                    uint32_t lifetime = pctGetLifetime(peek_ptr->pid);
                    feqInsert(FutureEventType::TERMINATE, lifetime + simTime, peek_ptr->pid);
                    pctUpdateState(peek_ptr->pid, ProcessState::ACTIVE, simTime, ptr);
                    swpRemove(i);
                }
            }
        }

        return true;
    }

// ================================================================================== //

} // end of namespace group
