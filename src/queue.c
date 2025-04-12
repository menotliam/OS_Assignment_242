#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// static int head_index = 0; // Index of the head of the queue
// static int tail_index = 0; // Index of the tail of the queue

int empty(struct queue_t * q) {
    if (q == NULL) return 1;
    return (q->size == 0);
}

void enqueue(struct queue_t *q, struct pcb_t *proc) {
    printf("Debug: Enqueuing process (PID: %d) to queue\n", proc->pid);
        if (q->size == MAX_QUEUE_SIZE) {
            printf("Queue is full, cannot enqueue.\n");
            return;
        }
        q->proc[q->tail_index] = proc;
        q->tail_index = (q->tail_index + 1) % MAX_QUEUE_SIZE; // Circular buffer logic
        q->size++;
    }
    
    struct pcb_t *dequeue(struct queue_t *q) {
        
        if (empty(q)) {
            printf("Queue is empty, cannot dequeue.\n");
            return NULL;
        }
        printf("Debug: Dequeuing process (PID: %d) from queue\n", q->proc[q->head_index]->pid);

        struct pcb_t *proc = q->proc[q->head_index];
        q->head_index = (q->head_index + 1) % MAX_QUEUE_SIZE; // Circular buffer logic
        q->size--;
        return proc;
}

