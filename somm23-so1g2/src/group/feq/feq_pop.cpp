/*
 *  \author José Jordão (103075)
 */

#include "somm23.h"

namespace group {

// ==================================================================================
// //

FutureEvent feqPop() {
  soProbe(205, "%s()\n", __func__);
  require(feqHead != NULL, "future event queue must not be empty");

  FeqEventNode *aux = feqHead;
  feqHead = feqHead->next;

  return aux->event;
}

// ==================================================================================
// //

bool feqIsEmpty() {
  soProbe(206, "%s()\n", __func__);

  if (feqHead == NULL) {
    return true;
  } else {
    return false;
  }
}

// ==================================================================================
// //

} // end of namespace group
