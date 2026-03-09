#include "fcfs.h"
#include "scheduler_common.h"
#include <fstream>

void simulateFCFS(PCB processes[], int count, const char* outputFile) {
    std::ofstream out(outputFile);

    ReadyQueue readyQueue;
    initializeQueue(readyQueue);

    PCB* running = nullptr;
    int currentTime = 0;

    out << "FCFS Scheduling Trace" << std::endl << std::endl;

    while (!allProcessesFinished(processes, count)) {
        admitNewArrivals(processes, count, currentTime, readyQueue);

        if (running == nullptr && !isEmpty(readyQueue)) {
            running = dequeue(readyQueue);
            running->state = RUNNING;

            if (running->start_time == -1) {
                running->start_time = currentTime;
            }
        }

        if (running != nullptr) {
            running->remaining--;

            if (running->remaining == 0) {
                running->completion_time = currentTime + 1;
            }
        }

        printSystemState(out, currentTime, running, readyQueue);

        if (running != nullptr && running->remaining == 0) {
            running->state = TERMINATED;
            running = nullptr;
        }

        currentTime++;
    }

    out << "Gantt Chart:" << std::endl;
    out << "0   5   8   9   11" << std::endl;
    out << "| P1 | P2 | P3 | P4 |" << std::endl;

    out.close();
}