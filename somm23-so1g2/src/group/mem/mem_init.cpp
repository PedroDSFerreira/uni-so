/*
 *  \author Tomás Cerca Rodrigues (104090)
 */
#include "somm23.h"
#include <stdint.h>

namespace group {

// =======================================================================
// =========== //

void memInit(uint32_t mSize, uint32_t osSize, uint32_t cSize,
             AllocationPolicy policy) {
  const char *pas = policy == FirstFit      ? "FirstFit"
                    : policy == BuddySystem ? "BuddySystem"
                                            : "Unkown";
  soProbe(501, "%s(%#x, %#x, %#x, %s)\n", __func__, mSize, osSize, cSize, pas);
  require(mSize > osSize, "memory must be bigger than the one use by OS");
  require((mSize % cSize) == 0,
          "memory size must be a multiple of chunck size");
  require((osSize % cSize) == 0,
          "memory size for OS must be a multiple of chunck size");
  require(policy == FirstFit or policy == BuddySystem,
          "policy must be FirstFit or BuddySystem");

  // mSize -> memoria disponível
  // osSize -> memoria ocupada pelo OS
  // cSize -> a unidade de alocação em bytes

  memTreeRoot = NULL;
  memFreeHead = NULL;
  memOccupiedHead = NULL;

  memParameters.chunkSize = cSize;
  memParameters.kernelSize = osSize;
  memParameters.totalSize = mSize;
  memParameters.policy = policy;

  switch (policy) {
  case FirstFit: {
    memFreeHead = new MemListNode();
    memFreeHead->block.address =
        osSize; // The free block starts where the OS ends (osSize)
    memFreeHead->block.size = mSize - osSize;
    memOccupiedHead =  nullptr;
    break;
  }

  case BuddySystem: {
    memTreeRoot = new MemTreeNode();
    if (memTreeRoot == NULL) {
      printf("Failed to allocate memory for the buddy system tree");
      return;
    }

    uint32_t blockSize = 1;
    while (blockSize < mSize / 2) {
      blockSize *= 2;
    }

    memTreeRoot->block.size = blockSize; // The size of the block is 2^N * cSize
    memTreeRoot->state = FREE;           // o node está livre
    memTreeRoot->block.address =
        osSize; // The address of the block is the last address used by the OS
    memTreeRoot->block.pid = 0; // No process has been assigned to the block
    break;
  }

  default:
    throw Exception(EINVAL, __func__);
    break;
  }
}

// ==================================================================================
// //

} // end of namespace group
