/*
 *  \author José Jordão (103075)
 */

#include "somm23.h"
#include <stdint.h>

namespace group {

// ==================================================================================
// //

void feqInit() {
  soProbe(201, "%s()\n", __func__);

  feqHead = NULL;
}
// ==================================================================================
// //

} // end of namespace group
