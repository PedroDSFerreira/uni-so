/*
 *  \author Tomás Cerca Rodrigues 104090
 */
 

#include "somm23.h"

#include <stdint.h>
#include <stdio.h>

namespace group {

// ================================================================================== //
void memFirstFitPrint(FILE *fout);
void memBuddySystemPrint(FILE *fout);
void memPrintHeader(FILE *fout, const char *header);
void memBuddySystemPrintRecursive(FILE *fout, MemTreeNode *node, MemTreeNodeType state);
void memPrint(FILE *fout) {
    soProbe(503, "%s(\"%p\")\n", __func__, fout);

    require(fout != NULL and fileno(fout) != -1, "fout must be a valid file stream");

    if (memParameters.policy == FirstFit) {
        memFirstFitPrint(fout);
    } else if (memParameters.policy == BuddySystem) {
        memBuddySystemPrint(fout);
    } else {
        throw Exception(EINVAL, __func__);
    }
}
void memPrintHeader(FILE *fout, const char *header) {
    fprintf(fout, "+====================================+\n");
    fprintf(fout, "%s", header);
    fprintf(fout, "+---------+-------------+------------+\n");
    fprintf(fout, "|   PID   |   address   |    size    |\n");
    fprintf(fout, "+---------+-------------+------------+\n");
}

void memFirstFitPrint(FILE *fout) {
    memPrintHeader(fout, "|   FirstFit memory occupied blocks  |\n");

    MemListNode *aux = memOccupiedHead;

    while (aux != NULL) {
        fprintf(fout, "| %7d | %#11x | %10d |\n", aux->block.pid, aux->block.address, aux->block.size);
        aux = aux->next;
    }
    fprintf(fout, "+====================================+\n\n");

    memPrintHeader(fout, "|     FirstFit memory free blocks    |\n");

    aux = memFreeHead;

    while (aux != NULL) {
        fprintf(fout, "|   ---   | %#11x | %10d |\n", aux->block.address, aux->block.size);
        aux = aux->next;
    }
    fprintf(fout, "+====================================+\n\n");
}

void memBuddySystemPrint(FILE *fout) {
    memPrintHeader(fout, "| BuddySystem memory occupied blocks |\n");

    memBuddySystemPrintRecursive(fout, memTreeRoot, MemTreeNodeType::OCCUPIED);

    fprintf(fout, "+====================================+\n\n");

    memPrintHeader(fout, "|   BuddySystem memory free blocks   |\n");

    memBuddySystemPrintRecursive(fout, memTreeRoot, MemTreeNodeType::FREE);
    fprintf(fout, "+====================================+\n\n");
}

void memBuddySystemPrintRecursive(FILE *fout, MemTreeNode *node, MemTreeNodeType state) {
    if (node == NULL)
        return;

    memBuddySystemPrintRecursive(fout, node->left, state);
    if (node->state == state) {
        if (state == MemTreeNodeType::FREE) {
            fprintf(fout, "|   ---   | %#11x | %10d |\n", node->block.address, node->block.size);
        }
        if (state == MemTreeNodeType::OCCUPIED) {
            fprintf(fout, "| %7d | %#11x | %10d |\n", node->block.pid, node->block.address, node->block.size);
        }
    }
    memBuddySystemPrintRecursive(fout, node->right, state);
}

// ================================================================================== //

} // end of namespace group
