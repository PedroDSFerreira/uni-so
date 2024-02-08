/*
 *  \author Carlos Ferreira (108822)
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    void simLoad(const char *fname)
    {
        soProbe(104, "%s(\"%s\")\n", __func__, fname);
        require(fname != NULL, "fname can not be a NULL pointer");
        require(forthcomingTable.count == 0, "Forthcoming table should be empty");

        FILE *fp = NULL;
        char *line = NULL;
        size_t len = 0;
        ssize_t read = 0;

        // open the file
        fp = fopen(fname, "r");
        if (fp == NULL) {
            throw Exception(errno, __func__);
        }

        // read line by line
        int line_number = 1;
        while ((read = getline(&line, &len, fp)) != -1) {
            uint32_t pid, arrival_time, lifetime;
            int32_t address_space_profile[MAX_SEGMENTS];
            char *line_ptr = line;

            // increase the line number
            line_number++;

            // ignore the white space at the beginning of the line
            while (*line_ptr != '\0' && *line_ptr == ' ') line_ptr++;

            // end the line at the "%" if there is one and ignore the new line char
            for (char *p = line_ptr; *p != '\0'; p++) {
                if (*p == '%' || *p == '\n') {
                    *p = '\0';
                    break;
                }
            }

            // if line size is 0 then ignore it
            size_t line_size = 0;
            for (char *p = line_ptr; *p != '\0'; p++) {
                line_size++;
            }

            if (line_size == 0) {
                continue;
            }

            // load the pid, arrival time and lifetime
            sscanf(line_ptr, " %d ; %d ; %d ;", &pid, &arrival_time, &lifetime);

            // find the last ";"
            char *last_field = NULL;
            int semicolon_count = 0;
            for (char *p = line_ptr; *p != '\0'; p++) {
                if (*p == ';') {
                    last_field = p + 1;
                    semicolon_count++;
                }
            }

            // make sure we have the right number of ";" and parse the last field
            if (last_field != NULL and semicolon_count == 3) {
                for (int32_t i = 0; i < MAX_SEGMENTS; i++) {
                    address_space_profile[i] = -1;
                }

                int i = 0;
                while (*last_field != '\0') {
                    // counter for error (malformed file) reporting
                    uint32_t counter = 0;

                    // check for too many segments in the line
                    if (i >= MAX_SEGMENTS) {
                        fprintf(stderr, "%s: syntax error at line %d: too many segments\n", __func__, line_number - 1);
                        throw Exception(EINVAL, __func__);
                    }

                    // ignore the spaces
                    while (*last_field == ' ' && *last_field != '\0') {
                        last_field++;
                        counter++;
                    }

                    // convert the string to a number
                    const int res = atoi(last_field);
                    address_space_profile[i] = res;
                    i++;

                    // add to counter the number of digits in 'res'
                    int tmp = res;
                    while (tmp != 0) {
                        tmp /= 10;
                        counter++;
                    }

                    // ignore the current number
                    while (*last_field >= '0' && *last_field <= '9') last_field++;
                    // find the next ',' or the end of the line (we may find a number in a not well formated file)
                    while (*last_field != '\0' && *last_field != ',' && !(*last_field >= '0' && *last_field <= '9')) {
                        last_field++;
                        counter++;
                    }

                    // check for number without a comma
                    if (*last_field >= '0' && *last_field <= '9') {
                        printf("%s: syntax error at line %d; %d\n", __func__, line_number - 1, counter);
                        throw Exception(EINVAL, __func__); 
                    }

                    if (*last_field == ',') last_field++; // ignore the comma
                }
            } else {
                printf("%s: syntax error at line %d; %d; 0\n", __func__, line_number - 1, semicolon_count + 1);
                throw Exception(EINVAL, __func__);
            }

            // add the new process to the table
            forthcomingTable.count++;
            forthcomingTable.process[forthcomingTable.count - 1].pid = pid;
            forthcomingTable.process[forthcomingTable.count - 1].arrivalTime = arrival_time;
            forthcomingTable.process[forthcomingTable.count - 1].lifetime = lifetime;

            // fill in the memory segments
            for (int32_t i = 0; i < MAX_SEGMENTS && address_space_profile[i] != -1; i++) {
                forthcomingTable.process[forthcomingTable.count - 1].addressSpace.segmentCount++;
                forthcomingTable.process[forthcomingTable.count - 1].addressSpace.size[i] = address_space_profile[i];
            }

            // add a new event to feq
            feqInsert(FutureEventType::ARRIVAL, arrival_time, pid);
        }

        // free all resources
        fclose(fp);
        free(line);
    }

// ================================================================================== //

} // end of namespace group
