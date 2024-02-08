/*
 *  \author Pedro Ferreira (98620)
 */

#include "somm23.h"

namespace group {

// ==================================================================================
// //

void feqInsert(FutureEventType type, uint32_t time, uint32_t pid) {
  const char *tas = type == ARRIVAL     ? "ARRIVAL"
                    : type == TERMINATE ? "TERMINATE"
                                        : "UNKNOWN";

  soProbe(204, "%s(%s, %u, %u)\n", __func__, tas, time, pid);
  require(pid > 0, "process ID must be non-zero");

  FeqEventNode *newNode = (FeqEventNode *)malloc(sizeof(FeqEventNode));
  newNode->event.type = type;
  newNode->event.time = time;
  newNode->event.pid = pid;
  newNode->next = NULL;

  if (feqHead == NULL || feqHead->event.time > newNode->event.time ||
      ((feqHead->event.time == newNode->event.time &&
        feqHead->event.type == ARRIVAL) &&
       type == TERMINATE)) {
    // Insert at the beginning
    newNode->next = feqHead;
    feqHead = newNode;
  } else {
    // Insert in the middle or at the end
    FeqEventNode *curr = feqHead;

    for (; curr->next != NULL; curr = curr->next) {
      if (newNode->event.time < curr->next->event.time || (curr->next->event.time == newNode->event.time && curr->next->event.type == ARRIVAL && type == TERMINATE)) {
        break;
      }
    }

    newNode->next = curr->next;
    curr->next = newNode;
  }
}

} // end of namespace group
