/*
 *  \author Tomás Cerca Rodrigues 104090
 */
 

#include "somm23.h"

#include <stdint.h>
namespace group {

// ================================================================================== //

void mergeContiguousBlocks();

void memFirstFitFree(Address address) {
    soProbe(508, "%s(0x%x)\n", __func__, address);

    require(memOccupiedHead != NULL, "Occupied list should contain nodes");

    MemListNode *aux = memOccupiedHead;
    MemListNode *prev = NULL;

    while (aux != NULL) {
        if (aux->block.address == address) {
            if (prev == NULL) {
                memOccupiedHead = aux->next;
            } else {
                prev->next = aux->next;
                if (aux->next != NULL) {
                    aux->next->prev = prev;
                }
            }

            MemListNode *auxFree = memFreeHead;
            MemListNode *prevFree = NULL;

            while (auxFree != NULL) {
                if (auxFree->block.address > aux->block.address) {
                    break;
                }

                prevFree = auxFree;
                auxFree = auxFree->next;
            }

            if (prevFree == NULL) {
                memFreeHead = aux;
            } else {
                prevFree->next = aux;
            }

            aux->prev = prevFree;
            aux->next = auxFree;
            if (auxFree != NULL) {
                auxFree->prev = aux;
            }
            mergeContiguousBlocks();
            return;
        }

        prev = aux;
        aux = aux->next;
    }
    throw Exception(EINVAL, __func__);
}

// ================================================================================== //

void mergeContiguousBlocks() {
    MemListNode *aux = memFreeHead;

    while (aux != NULL) {
        if (aux->prev == NULL) {
            aux = aux->next;
            continue;
        }
        if (aux->prev->block.address + aux->prev->block.size == aux->block.address) {
            aux->prev->block.size += aux->block.size;
            if (aux->next != NULL) {
                aux->next->prev = aux->prev;
                aux->prev->next = aux->next;
            } else {
                aux->prev->next = NULL;
            }
        }
        aux = aux->next;
    }
}

} // end of namespace group