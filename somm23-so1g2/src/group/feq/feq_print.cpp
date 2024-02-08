/*
 *  \author Pedro Ferreira (98620)
 */

#include "somm23.h"
#include <stdint.h>
#include <stdio.h>

namespace group {

// ==================================================================================
// //

void feqPrint(FILE *fout) {
  soProbe(203, "%s(\"%p\")\n", __func__, fout);

  require(fout != NULL and fileno(fout) != -1,
          "fout must be a valid file stream");

  fprintf(fout, "+==============================+\n"
                "|      Future Event Queue      |\n"
                "+----------+-----------+-------+\n"
                "|   time   |   type    |  PID  |\n"
                "+----------+-----------+-------+\n");

  FeqEventNode *curr = feqHead;
  while (curr != NULL) {
    if (curr->event.type == ARRIVAL) {
      fprintf(fout, "|%9d | %-9s | %5d |\n", curr->event.time, "ARRIVAL",
              curr->event.pid);

    } else if (curr->event.type == TERMINATE) {
      fprintf(fout, "|%9d | %-9s | %5d |\n", curr->event.time, "TERMINATE",
              curr->event.pid);
    }
    curr = curr->next;
  }

  fprintf(fout, "+==============================+\n\n");
}

// ==================================================================================
// //

} // end of namespace group
