#ifndef PCB_H
#define PCB_H

#include <string>

enum ProcessState {
    NEW,
    READY,
    RUNNING,
    TERMINATED
};

struct PCB {
    std::string pid;      // Process ID (P1, P2, etc.)
    int arrival;          // Arrival time
    int burst;            // Total CPU burst time
    int remaining;        // Remaining CPU time
    int priority;         // Priority level

    ProcessState state;   // Current process state

    int start_time;       // First time process gets CPU
    int completion_time;  // Time process finishes
};

#endif