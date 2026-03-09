#include "priority.h"
#include "scheduler_common.h"
#include <fstream>
#include <string>

PCB* selectHighestPriority(PCB processes[], int count) {
    PCB* best = nullptr;

    for (int i = 0; i < count; i++) {
        if (processes[i].state == READY) {
            if (best == nullptr || processes[i].priority < best->priority) {
                best = &processes[i];
            }
        }
    }

    return best;
}

void simulatePriority(PCB processes[], int count, const char* outputFile) {
    std::ofstream out(outputFile);

    PCB* running = nullptr;
    int currentTime = 0;

    // Gantt chart storage
    std::string gantt[100];
    int ganttIndex = 0;

    out << "Priority Scheduling Trace\n\n";

    while (!allProcessesFinished(processes, count)) {
        // Admit newly arrived processes
        admitNewArrivalsNoQueue(processes, count, currentTime);

        // If CPU is idle, select highest-priority READY process
        if (running == nullptr) {
            PCB* next = selectHighestPriority(processes, count);

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

        // Print system state
        printSystemStateFromArray(out, currentTime, running, processes, count);

        // If finished, terminate process
        if (running != nullptr && running->remaining == 0) {
            running->state = TERMINATED;
            running = nullptr;
        }

        currentTime++;
    }

    // Print Gantt chart
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