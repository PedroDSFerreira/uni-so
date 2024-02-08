/*
 *  \author Pedro Ferreira (98620)
 */

#include "somm23.h"
#include <stdint.h>
#include <stdio.h>

namespace group
{

    // ==================================================================================

    void swpPrint(FILE *fout)
    {
        soProbe(403, "%s(\"%p\")\n", __func__, fout);
        require(fout != NULL and fileno(fout) != -1, "fout must be a valid file stream");

        fprintf(fout, "+===============================================+\n");
        fprintf(fout, "|             Swapped Process Queue             |\n");
        fprintf(fout, "+-------+---------------------------------------+\n");
        fprintf(fout, "|  PID  |         address space profile         |\n");
        fprintf(fout, "+-------+---------------------------------------+\n");

        SwpNode *current = swpHead;
        while (current != NULL)
        {
            fprintf(fout, "|%6d |", current->process.pid);

            // Print address space profile based on MAX_BLOCKS
            for (int i = 0; i < MAX_BLOCKS; ++i)
            {
                if (current->process.profile.size[i] == 0 || current->process.profile.size[i] == (uint32_t)-1) {
                    // center "---" in 8 spaces
                    fprintf(fout, "   %s   ", "---");
                } else {
                    fprintf(fout, "%8d ", current->process.profile.size[i]);
                }

                if (i != MAX_BLOCKS - 1) {
                    fprintf(fout, ":");
                } else {
                    fprintf(fout, "|");
                }
            }

            fprintf(fout, "\n");
            current = current->next;
        }

        fprintf(fout, "+===============================================+\n\n");
    }

    // ==================================================================================

} // end of namespace group
