/*
 *  \author Carlos Ferreira (108822)
 */

#include <unistd.h>
#include "somm23.h"

static uint32_t randBetween(uint32_t n1, uint32_t n2 /*, double pzero, bool tens*/) {
    // Generate a random number between 0 and 1
    const double randValue = (double)rand() / RAND_MAX;

    // Calculate the random number within the specified range
    const uint32_t n = n1 + (uint32_t)(randValue * (double)(n2 - n1 + 1));

    // // Check the probability of having zero and adjust the result accordingly
    // if (pzero > 0.0 && randValue < pzero) {
    //     n = 0;
    // }
    // // Adjust the result to the nearest multiple of 10 if 'tens' is true
    // if (tens && n % 10 != 0) {
    //     n = (n / 10) * 10 + 10;
    // }

    return n;
}

namespace group
{

// ================================================================================== //

    void simRandomFill(uint32_t n, uint32_t seed)
    {
        soProbe(105, "%s(%u, %u)\n", __func__, n, seed);
        require(n == 0 or n >= 2, "At least 2 processes are required");
        require(n <= MAX_PROCESSES, "More than MAX_PROCESSES processes not allowed");

        // seed for random generator
        srand(seed == 0 ? getpid() : seed);

        // number of processes
        if (n == 0) {
            n = randBetween(2, MAX_PROCESSES);
        }

        // generate all the PIDs for the processes
        uint32_t pids[n];
        for (uint32_t count = 0; count < n;) {
            // generate new PID in [1, 65535]
            const uint32_t pid = randBetween(1, 65535);

            // make sure the pid is not yet being used by another process
            bool used = false;
            for (uint32_t i = 0; i < count; i++) {
                used = pids[i] == pid;
            }

            // add the new pid
            if (!used) {
                pids[count] = pid;
                count++;
            }
        }

        // generate the arrival times
        uint32_t arrival_times[n];
        arrival_times[0] = randBetween(0, 100);
        for (uint32_t i = 1; i < n; i++) {
            arrival_times[i] = randBetween(arrival_times[i - 1], arrival_times[i - 1] + 100);
        }

        // generate the lifetimes and address space segments
        uint32_t lifetimes[n];
        uint32_t number_of_segments[n];
        for (uint32_t i = 0; i < n; i++) {
            // lifetimes
            lifetimes[i] = randBetween(10, 1000);

            // number of address spaces per process
            number_of_segments[i] = randBetween(1, MAX_SEGMENTS);
        }

        // generate the size for all the address spaces, add processes to the table and to feq
        for (uint32_t i = 0; i < n; i++) {
            // add the new process to the table
            forthcomingTable.count++;
            forthcomingTable.process[forthcomingTable.count - 1].pid = pids[i];
            forthcomingTable.process[forthcomingTable.count - 1].arrivalTime = arrival_times[i];
            forthcomingTable.process[forthcomingTable.count - 1].lifetime = lifetimes[i];

            // fill in the memory segments
            forthcomingTable.process[forthcomingTable.count - 1].addressSpace.segmentCount = number_of_segments[i];
            for (uint32_t j = 0; j < number_of_segments[i]; j++) {
                forthcomingTable.process[forthcomingTable.count - 1].addressSpace.size[j] = randBetween(0x100, 0x800);
            }

            // add a new event to feq
            feqInsert(FutureEventType::ARRIVAL, arrival_times[i], pids[i]);
        }
    }

// ================================================================================== //

} // end of namespace group
