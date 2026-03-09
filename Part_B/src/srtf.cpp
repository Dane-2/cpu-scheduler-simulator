#include "srtf.h"
#include "scheduler_common.h"
#include <fstream>
#include <string>

PCB* selectShortestRemaining(PCB processes[], int count) {
    PCB* best = nullptr;

    for (int i = 0; i < count; i++) {
        if (processes[i].state == READY) {
            if (best == nullptr || processes[i].remaining < best->remaining) {
                best = &processes[i];
            }
        }
    }

    return best;
}

void simulateSRTF(PCB processes[], int count, const char* outputFile) {
    std::ofstream out(outputFile);

    PCB* running = nullptr;
    int currentTime = 0;

    std::string gantt[100];
    int ganttIndex = 0;

    out << "SRTF Scheduling Trace\n\n";

    while (!allProcessesFinished(processes, count)) {
        admitNewArrivalsNoQueue(processes, count, currentTime);

        PCB* shortestReady = selectShortestRemaining(processes, count);

        // Preemption rule:
        // preempt only if a READY process has strictly smaller remaining time
        if (running != nullptr && shortestReady != nullptr &&
            shortestReady->remaining < running->remaining) {
            running->state = READY;
            running = shortestReady;
            running->state = RUNNING;

            if (running->start_time == -1) {
                running->start_time = currentTime;
            }
        }

        // If CPU idle, dispatch shortest READY process
        if (running == nullptr) {
            PCB* next = selectShortestRemaining(processes, count);

            if (next != nullptr) {
                running = next;
                running->state = RUNNING;

                if (running->start_time == -1) {
                    running->start_time = currentTime;
                }
            }
        }

        // Execute one time unit
        if (running != nullptr) {
            running->remaining--;

            if (running->remaining == 0) {
                running->completion_time = currentTime + 1;
            }
        }

        // Record Gantt chart
        if (running == nullptr) {
            gantt[ganttIndex] = "IDLE";
        } else {
            gantt[ganttIndex] = running->pid;
        }
        ganttIndex++;

        // Print full PCB trace
        printSystemStateFromArray(out, currentTime, running, processes, count);

        // Terminate if finished
        if (running != nullptr && running->remaining == 0) {
            running->state = TERMINATED;
            running = nullptr;
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