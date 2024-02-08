/*
 *  \author José Jordão
 */

#include "somm23.h"

namespace group {

// ==================================================================================
// //

void memFree(AddressSpaceMapping *mapping) {
  soProbe(507, "%s(mapping: %p)\n", __func__, mapping);

  require(mapping != nullptr,
          "mapping must be a valid pointer to a AddressSpaceMapping");

  for (uint32_t i = 0; i < mapping->blockCount; ++i) {
    if (memParameters.policy == AllocationPolicy::FirstFit) {
      memFirstFitFree(mapping->address[i]);
    } else if (memParameters.policy == AllocationPolicy::BuddySystem) {
      memBuddySystemFree(mapping->address[i]);
    } else {
      throw Exception(ENOSYS, __func__); // Unsupported allocation policy
    }
  }
}

// ==================================================================================
// //

} // end of namespace group
