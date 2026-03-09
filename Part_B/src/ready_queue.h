#ifndef READY_QUEUE_H
#define READY_QUEUE_H

#include <iostream>
#include "pcb.h"

void admitNewArrivalsNoQueue(PCB processes[], int count, int currentTime);
void printReadyProcessesFromArray(std::ofstream& out, PCB processes[], int count);
void printSystemStateFromArray(std::ofstream& out, int time, PCB* running, PCB processes[], int count);

struct QueueNode {
    PCB* process;
    QueueNode* next;
};

struct ReadyQueue {
    QueueNode* front;
    QueueNode* rear;
};

inline void initializeQueue(ReadyQueue& q) {
    q.front = nullptr;
    q.rear = nullptr;
}

inline bool isEmpty(const ReadyQueue& q) {
    return q.front == nullptr;
}

inline void enqueue(ReadyQueue& q, PCB* process) {
    QueueNode* newNode = new QueueNode;
    newNode->process = process;
    newNode->next = nullptr;

    if (q.rear == nullptr) {
        q.front = newNode;
        q.rear = newNode;
    } else {
        q.rear->next = newNode;
        q.rear = newNode;
    }
}

inline PCB* dequeue(ReadyQueue& q) {
    if (isEmpty(q)) {
        return nullptr;
    }

    QueueNode* temp = q.front;
    PCB* process = temp->process;
    q.front = q.front->next;

    if (q.front == nullptr) {
        q.rear = nullptr;
    }

    delete temp;
    return process;
}

inline void clearQueue(ReadyQueue& q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
}


#endif