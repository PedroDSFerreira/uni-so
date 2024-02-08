/*
 *  \author Daniel Emídio (108986)
 */

#include <stdio.h>
#include <stdint.h>
#include "somm23.h"

namespace group
{

// ================================================================================== //

    void simPrint(FILE *fout)
    {
        soProbe(103, "%s(\"%p\")\n", __func__, fout);
        require(fout != NULL and fileno(fout) != -1, "fout must be a valid file stream");

        // print table header
        fprintf(fout, "+====================================================================+\n"
                      "|                          forthcomingTable                          |\n"
                      "+-------+---------+----------+---------------------------------------+\n"
                      "|    Simulation step:%7d |              Simulation time:%8d |\n"
                      "+-------+---------+----------+---------------------------------------+\n"
                      "|  PID  | arrival | lifetime |         address space profile         |\n"
                      "+-------+---------+----------+---------------------------------------+\n", stepCount, simTime);

        // loop over every process in the table
        for (uint32_t i = 0; i < forthcomingTable.count; i++) {
            // print the pid, arrival time and lifetime
            fprintf(fout, "|%6d |%8d |%9d |",
                        forthcomingTable.process[i].pid, forthcomingTable.process[i].arrivalTime, forthcomingTable.process[i].lifetime);

            // print the address space profile
            for (uint32_t count = 0; count < MAX_BLOCKS; count++) {
                if (count < forthcomingTable.process[i].addressSpace.segmentCount) {
                    fprintf(fout, "%8d ", forthcomingTable.process[i].addressSpace.size[count]);
                } else {
                    fprintf(fout, "   ---   ");
                }

                if (count != MAX_BLOCKS - 1) {
                    fprintf(fout, ":");
                }
            }

            // print separation
            fprintf(fout, "|\n");
        }

        // print table footer
        fprintf(fout, "+====================================================================+\n\n");
    }

// ================================================================================== //

} // end of namespace group
