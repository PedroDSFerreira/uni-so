/*
 *  \author Pedro Ferreira (98620)
 */

#include "somm23.h"
#include <stdint.h>

namespace group {

// ==================================================================================
// //

Address memFirstFitAlloc(uint32_t pid, uint32_t size) {
    soProbe(505, "%s(%u, %#x)\n", __func__, pid, size);

    require(pid > 0, "A valid process ID must be greater than zero");
    require(size > 0, "The size of a memory segment must be greater than zero");

    MemListNode *current = memFreeHead;
    MemListNode *prev = nullptr;

    while (current != nullptr) {
        if (current->block.size >= size) {
            // Allocate memory from the current block
            MemBlock allocatedBlock = {pid, size, current->block.address};
            current->block.address += size;
            current->block.size -= size;

            // If the block is fully allocated, remove it from the free list
            if (current->block.size == 0) {
                if (prev != nullptr) {
                    prev->next = current->next;
                } else {
                    memFreeHead = current->next;
                }

                if (current->next != nullptr) {
                    current->next->prev = prev;
                }

                // Deallocate the node
                delete current;
            }

            // Add the allocated block to the occupied list in ascending order of block addresses
            MemListNode *occupiedNode = new MemListNode{allocatedBlock, nullptr, nullptr};

            // If the list is empty or the new node should be the head
            if (memOccupiedHead == nullptr || memOccupiedHead->block.address > allocatedBlock.address) {
                occupiedNode->next = memOccupiedHead;
                if (memOccupiedHead != nullptr) {
                    memOccupiedHead->prev = occupiedNode;
                }
                memOccupiedHead = occupiedNode;
            } else {
                // Otherwise, traverse to the correct position and add the new node
                MemListNode *currentOccupied = memOccupiedHead;

                while (currentOccupied->next != nullptr && currentOccupied->next->block.address < allocatedBlock.address) {
                    currentOccupied = currentOccupied->next;
                }

                occupiedNode->next = currentOccupied->next;
                if (currentOccupied->next != nullptr) {
                    currentOccupied->next->prev = occupiedNode;
                }
                occupiedNode->prev = currentOccupied;
                currentOccupied->next = occupiedNode;
            }

            return allocatedBlock.address;
        }

        prev = current;
        current = current->next;
    }

    // No block found
    return NULL_ADDRESS;
}

// ==================================================================================
// //

} // end of namespace group
