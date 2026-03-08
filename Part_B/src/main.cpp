#include <iostream>
#include <fstream>
#include <string>
#include "pcb.h"
#include "ready_queue.h"

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

int main() {
    PCB processes[MAX_PROCESSES];
    int processCount = loadProcesses("input.txt", processes);

    if (processCount == 0) {
        std::cout << "No processes loaded.\n";
        return 1;
    }

    ReadyQueue readyQueue;
    initializeQueue(readyQueue);

    for (int i = 0; i < processCount; i++) {
        processes[i].state = READY;
        enqueue(readyQueue, &processes[i]);
    }

    std::cout << "READY QUEUE CONTENTS:\n";
    printQueue(readyQueue);

    std::cout << "\nDequeuing one process...\n";
    PCB* first = dequeue(readyQueue);

    if (first != nullptr) {
        std::cout << "Removed: " << first->pid << std::endl;
    }

    std::cout << "\nREADY QUEUE AFTER DEQUEUE:\n";
    printQueue(readyQueue);

    return 0;
}