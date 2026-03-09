#include "scheduler_common.h"
#include <iostream>

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

void resetProcesses(PCB processes[], int count) {
    for (int i = 0; i < count; i++) {
        processes[i].remaining = processes[i].burst;
        processes[i].state = NEW;
        processes[i].start_time = -1;
        processes[i].completion_time = -1;
    }
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

void printRunningProcess(std::ofstream& out, PCB* running) {
    out << "RUNNING :" << std::endl;

    if (running == nullptr) {
        out << "IDLE" << std::endl;
    } else {
        out << "PID = " << running->pid
            << " Arr =" << running->arrival
            << " Burst =" << running->burst
            << " Rem =" << running->remaining
            << " Prio =" << running->priority
            << " State = " << stateToString(running->state)
            << std::endl;
    }
}

void printReadyQueue(std::ofstream& out, const ReadyQueue& readyQueue) {
    QueueNode* current = readyQueue.front;

    while (current != nullptr) {
        PCB* p = current->process;
        out << "PID = " << p->pid
            << " Arr =" << p->arrival
            << " Burst =" << p->burst
            << " Rem =" << p->remaining
            << " Prio =" << p->priority
            << " State = READY" << std::endl;
        current = current->next;
    }
}

void printSystemState(std::ofstream& out, int time, PCB* running, const ReadyQueue& readyQueue) {
    out << "Time " << time << ":" << std::endl;
    printRunningProcess(out, running);
    out << "READY :" << std::endl;
    printReadyQueue(out, readyQueue);
    out << std::endl;
}

void admitNewArrivals(PCB processes[], int count, int currentTime, ReadyQueue& readyQueue) {
    for (int i = 0; i < count; i++) {
        if (processes[i].state == NEW && processes[i].arrival == currentTime) {
            processes[i].state = READY;
            enqueue(readyQueue, &processes[i]);
        }
    }
}

bool allProcessesFinished(PCB processes[], int count) {
    for (int i = 0; i < count; i++) {
        if (processes[i].state != TERMINATED) {
            return false;
        }
    }
    return true;
}