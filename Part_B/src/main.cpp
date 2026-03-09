#include <iostream>

#include "scheduler_common.h"

#include "fcfs.h"
#include "priority.h"
#include "srtf.h"
#include "rr.h"

int main() {
    PCB processes[MAX_PROCESSES];
    int processCount = loadProcesses("input.txt", processes);

    if (processCount == 0) {
        std::cout << "No processes loaded." << std::endl;
        return 1;
    }

    resetProcesses(processes, processCount);
    simulateFCFS(processes, processCount, "output_fcfs.txt");

    resetProcesses(processes, processCount);
    simulatePriority(processes, processCount, "output_priority.txt");

    resetProcesses(processes, processCount);
    simulateSRTF(processes, processCount, "output_srtf.txt");

    resetProcesses(processes, processCount);
    simulateRR(processes, processCount, 2, "output_rr.txt");

    std::cout << "FCFS simulation complete. Output written to output_fcfs.txt" << std::endl;
    std::cout << "Priority simulation complete. Output written to output_priority.txt" << std::endl;
    std::cout << "SRTF simulation complete. Output written to output_srtf.txt" << std::endl;
    std::cout << "Round Robin simulation complete. Output written to output_rr.txt" << std::endl;

    return 0;
}