#ifndef READY_QUEUE_H
#define READY_QUEUE_H

#include <iostream>
#include "pcb.h"

struct QueueNode {
    PCB* process;
    QueueNode* next;
};

struct ReadyQueue {
    QueueNode* front;
    QueueNode* rear;
};

void initializeQueue(ReadyQueue& q) {
    q.front = nullptr;
    q.rear = nullptr;
}

bool isEmpty(const ReadyQueue& q) {
    return q.front == nullptr;
}

void enqueue(ReadyQueue& q, PCB* process) {
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

PCB* dequeue(ReadyQueue& q) {
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

void printQueue(const ReadyQueue& q) {
    QueueNode* current = q.front;

    while (current != nullptr) {
        PCB* p = current->process;
        std::cout << "PID=" << p->pid
                  << " Arr=" << p->arrival
                  << " Burst=" << p->burst
                  << " Rem=" << p->remaining
                  << " Prio=" << p->priority
                  << std::endl;

        current = current->next;
    }
}

#endif