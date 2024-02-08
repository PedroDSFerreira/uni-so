/*
 *  \author Carlos Ferreira (108822)
 */

#include "somm23.h"

#include <stdio.h>
#include <stdint.h>

namespace group
{

// ================================================================================== //

    void pctPrint(FILE *fout)
    {
        soProbe(303, "%s(\"%p\")\n", __func__, fout);
        require(fout != NULL and fileno(fout) != -1, "fout must be a valid file stream");

        // print pct header
        fprintf(fout, "+====================================================================================================================================================+\n"
                      "|                                                                  Process Control Table                                                             |\n"
                      "+-------+-----------+---------+----------+---------+---------+---------------------------------------+-----------------------------------------------+\n"
                      "|  PID  |   state   | arrival | lifetime | active  | finish  |         address space profile         |             address space mapping             |\n"
                      "+-------+-----------+---------+----------+---------+---------+---------------------------------------+-----------------------------------------------+\n");

        // loop over all the nodes in the process control table
        for (PctNode *aux = pctHead; aux != NULL; aux = aux->next) {
            // print the pid, state, arrival, lifetime, active and finish
            const char *state = pctGetStateAsString(aux->pcb.pid);
            fprintf(fout, "|%6d | %-9s |%8d |%9d |",
                        aux->pcb.pid, state, aux->pcb.arrivalTime, aux->pcb.lifetime);

            if (aux->pcb.activationTime == NO_TIME) {
                fprintf(fout, "   ---   |");
            } else {
                fprintf(fout, "%8d |", aux->pcb.activationTime);
            }

            if (aux->pcb.finishTime == NO_TIME) {
                fprintf(fout, "   ---   |");
            } else {
                fprintf(fout, "%8d |", aux->pcb.finishTime);
            }

            // print the address space profile
            for (uint32_t count = 0; count < MAX_BLOCKS; count++) {
                if (count < aux->pcb.memProfile.segmentCount) {
                    fprintf(fout, "%8d ", aux->pcb.memProfile.size[count]);
                } else {
                    fprintf(fout, "   ---   ");
                }

                if (count != MAX_BLOCKS - 1) {
                    fprintf(fout, ":");
                }
            }

            // print separation
            fprintf(fout, "|");

            // print the address space mapping
            for (uint32_t count = 0; count < MAX_BLOCKS; count++) {
                if (count < aux->pcb.memMapping.blockCount) {
                    fprintf(fout, " %#09x ", aux->pcb.memMapping.address[count]);
                } else {
                    fprintf(fout, "    ---    ");
                }

                if (count != MAX_BLOCKS - 1) {
                    fprintf(fout, ":");
                }
            }

            // print separation
            fprintf(fout, "|\n");
        }

        // print pct footer
        fprintf(fout, "+====================================================================================================================================================+\n\n");
    }

// ================================================================================== //

} // end of namespace group
