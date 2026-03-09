#ifndef SCHEDULER_COMMON_H
#define SCHEDULER_COMMON_H

#include <fstream>
#include <string>
#include "pcb.h"
#include "ready_queue.h"

const int MAX_PROCESSES = 100;

int loadProcesses(const std::string& filename, PCB processes[]);
void resetProcesses(PCB processes[], int count);
const char* stateToString(ProcessState state);

void printRunningProcess(std::ofstream& out, PCB* running);
void printReadyQueue(std::ofstream& out, const ReadyQueue& readyQueue);
void printSystemState(std::ofstream& out, int time, PCB* running, const ReadyQueue& readyQueue);

void admitNewArrivals(PCB processes[], int count, int currentTime, ReadyQueue& readyQueue);
bool allProcessesFinished(PCB processes[], int count);

#endif