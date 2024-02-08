/*
 *  \author ...
 */

#include "somm23.h"

#include <stdint.h>

namespace group 
{

// ================================================================================== //

    MemTreeNode* DFS(MemTreeNode* node, Address address) {
        if (node == NULL) {
            return NULL;
        }
        if (node->block.address == address && node->state == OCCUPIED) {
            return node;
        }
        MemTreeNode* targetNode = DFS(node->left, address);
        if (targetNode == NULL) {
            targetNode = DFS(node->right, address);
        }
        return targetNode;
    }
    void merge(MemTreeNode* node){
        if (node->state == SPLITTED ){
            if (node->left->state == SPLITTED){
                merge(node->left);
            }
            if (node->right->state == SPLITTED){
                merge(node->right);
            }
        }
        // se tiver filhos e estes tiverem livres da merge
        if (node->state == SPLITTED && node->left->state == FREE && node->right->state == FREE) {
            node->state = FREE;
            free(node->left);
            free(node->right);
            node->left = NULL;
            node->right = NULL;
        }
    }
    void memBuddySystemFree(Address address)
    {
        soProbe(509, "%s(%u)\n", __func__, address);

        /* TODO POINT: Replace next instruction with your code */
        //If the block to be freed is contiguous to an empty block, merging must take place.

        if (address == NULL_ADDRESS) {
            throw Exception(EINVAL, __func__);
        }
        MemTreeNode *targetNode = DFS(memTreeRoot, address);
        if (targetNode == NULL || targetNode->state == FREE) {
            throw Exception(EINVAL, __func__);
        }
        targetNode->state = FREE;
        merge(memTreeRoot);
    }

// ================================================================================== //

} // end of namespace group
