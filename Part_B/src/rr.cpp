#include "rr.h"
#include "scheduler_common.h"
#include <fstream>
#include <string>

void simulateRR(PCB processes[], int count, int quantum, const char* outputFile) {
    std::ofstream out(outputFile);

    ReadyQueue readyQueue;
    initializeQueue(readyQueue);

    PCB* running = nullptr;
    int currentTime = 0;
    int timeSliceUsed = 0;

    std::string gantt[100];
    int ganttIndex = 0;

    out << "Round Robin Scheduling Trace\n\n";
    out << "Quantum = " << quantum << "\n\n";

    while (!allProcessesFinished(processes, count)) {
        admitNewArrivals(processes, count, currentTime, readyQueue);

        if (running == nullptr && !isEmpty(readyQueue)) {
            running = dequeue(readyQueue);
            running->state = RUNNING;
            timeSliceUsed = 0;

            if (running->start_time == -1) {
                running->start_time = currentTime;
            }
        }

        if (running != nullptr) {
            running->remaining--;
            timeSliceUsed++;

            if (running->remaining == 0) {
                running->completion_time = currentTime + 1;
            }
        }

        if (running == nullptr) {
            gantt[ganttIndex] = "IDLE";
        } else {
            gantt[ganttIndex] = running->pid;
        }
        ganttIndex++;

        printSystemState(out, currentTime, running, readyQueue);

        if (running != nullptr && running->remaining == 0) {
            running->state = TERMINATED;
            running = nullptr;
            timeSliceUsed = 0;
        }
        else if (running != nullptr && timeSliceUsed == quantum) {
            running->state = READY;
            enqueue(readyQueue, running);
            running = nullptr;
            timeSliceUsed = 0;
        }

        currentTime++;
    }

    out << "\nGantt Chart:\n";

    for (int i = 0; i <= ganttIndex; i++) {
        out << i << " ";
    }

    out << "\n";

    for (int i = 0; i < ganttIndex; i++) {
        out << "| " << gantt[i] << " ";
    }

    out << "|\n";

    out.close();
}