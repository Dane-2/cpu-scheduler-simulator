#include <iostream>
#include "scheduler_common.h"
#include "fcfs.h"

int main() {
    PCB processes[MAX_PROCESSES];
    int processCount = loadProcesses("input.txt", processes);

    if (processCount == 0) {
        std::cout << "No processes loaded." << std::endl;
        return 1;
    }

    resetProcesses(processes, processCount);
    simulateFCFS(processes, processCount, "output_fcfs.txt");

    std::cout << "FCFS simulation complete. Output written to output_fcfs.txt" << std::endl;

    return 0;
}