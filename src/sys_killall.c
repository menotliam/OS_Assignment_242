/*
 * Copyright (C) 2025 pdnguyen of HCMC University of Technology VNU-HCM
 */

/* Sierra release
 * Source Code License Grant: The authors hereby grant to Licensee
 * personal permission to use and modify the Licensed Source Code
 * for the sole purpose of studying while attending the course CO2018.
 */

#include "common.h"
#include "syscall.h"
#include "stdio.h"
#include "libmem.h"
#include "string.h"
#include "queue.h"
#include "stdlib.h"

#define NUM_LEVELS 3 // Number of levels in the multi-level queue

int __sys_killall(struct pcb_t *caller, struct sc_regs* regs)
{
    char proc_name[100];
    uint32_t data;

    //hardcode for demo only
    uint32_t memrg = regs->a1;
    
    /* TODO: Get name of the target proc */
    //proc_name = libread..
    int i = 0;
    data = 0;
    while(data != -1){
        libread(caller, memrg, i, &data);
        proc_name[i]= data;
        if(data == -1) proc_name[i]='\0';
        i++;
    }
    printf("The procname retrieved from memregionid %d is \"%s\"\n", memrg, proc_name);

    /* TODO: Traverse proclist to terminate the proc
     *       stcmp to check the process match proc_name
     */
    //caller->running_list
    //caller->mlq_ready_queue

    // Traverse the ready queue and terminate matching processes
    struct queue_t *mlq_ready_queue = caller->mlq_ready_queue;
    for (int queue_level = 0; queue_level < NUM_LEVELS; queue_level++) {
        struct queue_t *queue = &mlq_ready_queue[queue_level]; // Access each queue
        struct pcb_t *current_ready = dequeue(queue);
        struct queue_t temp_ready_queue = {0};

        while (current_ready != NULL) {
            if (strcmp(current_ready->path, proc_name) == 0) {
                printf("Terminating process: %s (PID: %d)\n", current_ready->path, current_ready->pid);
                free(current_ready); // Free the terminated process
            } else {
                enqueue(&temp_ready_queue, current_ready); // Add non-matching process to temp queue
            }
            current_ready = dequeue(queue);
        }

        // Restore the remaining processes back to the ready queue
        while ((current_ready = dequeue(&temp_ready_queue)) != NULL) {
            enqueue(queue, current_ready);
        }
    }

    return 0;
}
