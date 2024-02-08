/*
 *  \author ...
 */

#include "somm23.h"

#include <stdint.h>
#include <stdio.h>

namespace group 
{

// ================================================================================== //


    MemTreeNode* DFSandDivide(MemTreeNode *node, uint32_t blockSize){
        // node nao serve
        if (node == NULL || node->state == OCCUPIED || node->block.size < blockSize) {
            return NULL;
        }
        // node serve
        if (node->state == FREE && node->block.size == blockSize){
            return node;
        }
        // node precisa de ser dividido para servir
        // o node fica com state=Splitted e entra no proximo if
        //se block.size > blockSize , entao block.size é pelo menos o dobro de blockSize
        if (node->state == FREE && node->block.size > blockSize) {
           node->state = SPLITTED;
            node->left = new MemTreeNode();
            node->right = new MemTreeNode();
            node->left->block.pid =  node->block.pid;
            node->left->state = FREE;  
            node->left->block.size = node->block.size/2;
            node->left->block.address = node->block.address;

            node->right->block.pid =  node->block.pid;
            node->right->state = FREE; 
            node->right->block.size = node->block.size/2;
            node->right->block.address = (node->block.address + node->block.size/2); 
        }
        if (node->state == SPLITTED){
            MemTreeNode* targetnode = DFSandDivide(node->left,  blockSize);
            if (targetnode != NULL) {
                return targetnode;
            }
            return DFSandDivide(node->right,  blockSize);
        }else{
            // se chegar aqui é porque alguma coisa deu mal
            return NULL;
        }

    }
    Address memBuddySystemAlloc(uint32_t pid, uint32_t size)
    {
        soProbe(506, "%s(%u, %#x)\n", __func__, pid, size);

        require(pid > 0, "a valid process ID must be greater than zero");
        require(size, "the size of a memory segment must be greater then zero");

        /* TODO POINT: Replace next instruction with your code */
        // size	Size of the block to be allocated, in bytes
        // The first, best fit free block, according to a left-right, depth-first search, must be used.
        // The start address of the block allocated or NULL_ADDRESS if no block was found

         if(size <= 0 || pid <= 0) {
            throw Exception(EINVAL, __func__);
        }
        uint32_t blockSize = memParameters.chunkSize;                           // espaco em chunks necessario
        while (blockSize < size) {
            blockSize *= 2;
        }
        MemTreeNode* targetNode = DFSandDivide(memTreeRoot, blockSize);
        if (targetNode == NULL) {
            return NULL_ADDRESS;
        }
        targetNode->state = OCCUPIED;
        targetNode->block.pid = pid;
        return targetNode->block.address;
    }

// ================================================================================== //

} // end of namespace group
