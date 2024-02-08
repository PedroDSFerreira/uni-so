/*
 *  \author Daniel Emídio 108986
 */

#include "somm23.h"

void deallocate(MemTreeNode *node) {
  if (node == NULL) {
    return;
  }
  // now onto the recursion
  deallocate(node->left);
  deallocate(node->right);

  free(node);
}

namespace group {

// ==================================================================================
// //

void memTerm() {
  soProbe(502, "%s()\n", __func__);

  // term MemParameters
  memParameters.chunkSize = 0;
  memParameters.totalSize = 0;
  memParameters.kernelSize = 0;
  memParameters.policy = (AllocationPolicy)0;

  // term memFree
  MemListNode *currentFree = memFreeHead;
  MemListNode *nextFree = NULL;

  while (currentFree != NULL) {
    nextFree = currentFree->next;
    free(currentFree);
    currentFree = nextFree;
  }

  // term memOccupiedHead
  MemListNode *currentOccupied = memOccupiedHead;
  MemListNode *nextOccupied = NULL;

  while (currentOccupied != NULL) {
    nextOccupied = currentOccupied->next;
    free(currentOccupied);
    currentOccupied = nextOccupied;
  }

  // term memTreeRoot
  deallocate(memTreeRoot);

  /* TODO POINT: Replace next instruction with your code */
  // throw Exception(ENOSYS, __func__);
}

// ==================================================================================
// //

} // end of namespace group
