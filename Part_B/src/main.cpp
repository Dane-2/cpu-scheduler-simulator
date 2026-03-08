#include <iostream>
#include <fstream>
#include <string>
#include "pcb.h"

const int MAX_PROCESSES = 100;

int loadProcesses(const std::string& filename, PCB processes[]) {
    std::ifstream infile(filename);

    if (!infile) {
        std::cout << "Error: Could not open " << filename << std::endl;
        return 0;
    }

    int count = 0;

    while (count < MAX_PROCESSES &&
           infile >> processes[count].pid
                  >> processes[count].arrival
                  >> processes[count].burst
                  >> processes[count].priority) {

        processes[count].remaining = processes[count].burst;
        processes[count].state = NEW;
        processes[count].start_time = -1;
        processes[count].completion_time = -1;

        count++;
    }

    infile.close();
    return count;
}

const char* stateToString(ProcessState state) {
    switch (state) {
        case NEW: return "NEW";
        case READY: return "READY";
        case RUNNING: return "RUNNING";
        case TERMINATED: return "TERMINATED";
        default: return "UNKNOWN";
    }
}

void printProcesses(PCB processes[], int count) {
    std::cout << "Loaded Processes:\n";
    for (int i = 0; i < count; i++) {
        std::cout << "PID=" << processes[i].pid
                  << " Arr=" << processes[i].arrival
                  << " Burst=" << processes[i].burst
                  << " Rem=" << processes[i].remaining
                  << " Prio=" << processes[i].priority
                  << " State=" << stateToString(processes[i].state)
                  << " Start=" << processes[i].start_time
                  << " Completion=" << processes[i].completion_time
                  << std::endl;
    }
}

int main() {
    PCB processes[MAX_PROCESSES];

    int processCount = loadProcesses("input.txt", processes);

    if (processCount == 0) {
        std::cout << "No processes loaded.\n";
        return 1;
    }

    printProcesses(processes, processCount);

    return 0;
}