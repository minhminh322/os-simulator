#include <stdlib.h>
#include <stdio.h>
#include "partition.h"
#include "process.h"
#include "listADTgen.h"
#include "queue.h"


struct process_t
{
    unsigned short pid;
    unsigned int size;
    ListType frames_int; // Frame integer list
};

struct process_table_t {
    ListType process_type; // process_t list    

};

Process create_process(unsigned short thePid, unsigned int theSize) {
    /* Queue list that store frames per process. */
    Queue frame_queue_ptr = create(sizeof(int), NULL);

    Process procptr = malloc(sizeof(struct process_t)); // MEMORY LEAK
    procptr->pid = thePid;
    procptr->size = theSize;
    procptr->frames_int = frame_queue_ptr;
    return procptr;
}

Processtable create_process_table_list()
{
    ListType process_list_ptr = create(sizeof(struct process_t), NULL);

    Processtable ptptr = malloc(sizeof(struct process_table_t));
    ptptr->process_type = process_list_ptr;

    return ptptr;
}

void add_process(Processtable ptptr, unsigned short thePid, unsigned int theSize) {
    Process current_process = create_process(thePid, theSize);
    push(ptptr->process_type, current_process);
    free(current_process);
    
}

void add_frame_queue(Processtable ptptr, int queue_counter, int* frame_queue) {
    Process p = (Process)get(ptptr->process_type, queue_counter);
    queue_enqueue(p->frames_int, frame_queue);
}

int get_frame_index(Processtable ptptr, int process_id) {
    int i, del_index;
    int process_table_size = size_is(ptptr->process_type);

    for(i = 0; i < process_table_size; i++) {
        Process p = (Process)get(ptptr->process_type, i);
        if (p->pid == process_id) {
            del_index = i;
            break;
        }
    }
    return del_index;
}

int get_queue_size(Processtable ptptr, int process_index) {
    Process p = (Process)get(ptptr->process_type, process_index);
    return size_is(p->frames_int);
}

int *get_queue_frame(Processtable ptptr, int process_index) {
    int *dequeue;
    Process p = (Process)get(ptptr->process_type, process_index);
    dequeue = (int*) queue_dequeue(p->frames_int);

    return dequeue;
}

void delete_process(Processtable ptptr, int process_index) {
    int *rem = (int*)removeAtIndex(ptptr->process_type, process_index);
    free(rem);
}

void process_list_destroy(Processtable ptptr) {
    int i;
    int process_table_size = size_is(ptptr->process_type);

    // Destroy frame_int list
    for (i = 0; i < process_table_size; i++) {
        Process p = (Process)get(ptptr->process_type, i);
        destroy(p->frames_int);
    }

    destroy(ptptr->process_type);
    free(ptptr);
}

void print_process_table(Processtable ptptr) {
    int i;
    int process_table_size = size_is(ptptr->process_type);

    for (i = 0; i < process_table_size; i++)
    {
        Process p = (Process)get(ptptr->process_type, i);
        printf(" %4d                   ", p->pid);
        queue_print(p->frames_int);
        printf("\n");
    }
    
}

void printItem(int *p)
{
    printf("%d", *p);
}