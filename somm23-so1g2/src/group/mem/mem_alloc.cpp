/*
 *  \author José Jordão
 */

#include "somm23.h"

#include <stdint.h>

namespace group {

// ==================================================================================
// //

AddressSpaceMapping *memAlloc(uint32_t pid, AddressSpaceProfile *profile) {
  require(pid > 0, "process ID must be non-zero");
  require(profile != NULL,
          "profile must be a valid pointer to an AddressSpaceProfile variable");

  // Initialize mapping
  static AddressSpaceMapping theMapping = {0, {0}};

  // Round up each segment size to the nearest multiple of chunk size
  for (uint32_t i = 0; i < profile->segmentCount; i++) {
    uint32_t roundedSize = (profile->size[i] + memParameters.chunkSize - 1) /
                           memParameters.chunkSize * memParameters.chunkSize;
    profile->size[i] = roundedSize;
  }

  // Check if total allocated size exceeds available memory
  uint32_t totalAllocatedSize = 0;
  for (uint32_t i = 0; i < profile->segmentCount; i++) {
    totalAllocatedSize += profile->size[i];
    if (totalAllocatedSize >
        memParameters.totalSize - memParameters.kernelSize) {
      return IMPOSSIBLE_MAPPING;
    }
  }

  // Allocate memory segments using the specified policy
  theMapping = {0, {0}};
  for (uint32_t i = 0; i < profile->segmentCount; i++) {
    Address address = (memParameters.policy == FirstFit)
                          ? memFirstFitAlloc(pid, profile->size[i])
                          : memBuddySystemAlloc(pid, profile->size[i]);
    if (address == NULL_ADDRESS) {
      memFree(&theMapping);
      return NO_MAPPING;
    }
    theMapping.blockCount++;
    theMapping.address[i] = address;
  }

  return &theMapping;
}

} // namespace group

// ==================================================================================
// // end of namespace group
