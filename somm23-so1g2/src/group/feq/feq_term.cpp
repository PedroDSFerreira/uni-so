/*
 *  \author José Jordão (103075)
 */

#include "somm23.h"

namespace group {

// ==================================================================================
// //

void feqTerm() {
  soProbe(202, "%s()\n", __func__);

  while (feqHead != NULL) {
    FeqEventNode *aux = feqHead;
    feqHead = feqHead->next;
    delete aux;
  }
}

// ==================================================================================
// //

} // end of namespace group
