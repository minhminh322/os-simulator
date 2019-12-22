#include <stdlib.h>
#include <stdio.h>
#include "partition.h"
#include "process.h"
#include "listADTgen.h"
#include "queue.h"

struct frame_t
{
    short pid;
    int frag;
};

struct partition_table_t
{
    ListType frames_type; // frame_t list
};

/* Create a frame in partition table*/
Frame create_frame(short thePid, int theFrag) {
    Frame fptr = malloc(sizeof(struct frame_t));// MEMORY LEAK.
    fptr->pid = thePid;
    fptr->frag = theFrag;

    return fptr;
}

/* Create partition table. */
Partition create_partition_list(int partition_num) {
    int i;
    ListType partition_list_ptr = create(sizeof(struct frame_t), NULL);

    // Add number of partition to the list
    for (i = 0; i < partition_num; i++) {
        Frame current_frame = create_frame(-1, -1);
        push(partition_list_ptr, current_frame);
        free(current_frame);
    }
    
    // memory allocation partition_table_t struct
    Partition pptr = malloc(sizeof(struct partition_table_t)); // MEMORY LEAK
    // memcpy(&pptr->frames_type, &partition_list_ptr, sizeof(struct partition_table_t));
    pptr->frames_type = partition_list_ptr;

    return pptr;
}

/* Modify partition table list. Return current_frame */
void add_partition(Partition pptr, short thePid, int theFrag, int *frame_index) {

    Frame f = (Frame)get(pptr->frames_type, *frame_index);
    f->pid = thePid;
    f->frag = theFrag;
}

void delete_partition(Partition pptr, int del_index) {
    Frame f = (Frame)get(pptr->frames_type, del_index);
    f->pid = -1;
    f->frag = -1;
}

void partition_list_destroy(Partition pptr) {
    destroy(pptr->frames_type);
    free(pptr);
}

void print_partition_table(Partition pptr, int par_num) {
    int i;
    char unknown = '?';
    char avail = 'Y';
    char non_avail = 'N';
    for (i = 0; i < par_num; i++)
    {
        Frame f = (Frame)get(pptr->frames_type, i);
        if (f->pid == -1 && f->frag == -1)
        {
            printf(" %7d %20c %13c %10c \n", i, unknown, unknown, avail);
        }
        else
        {
            printf(" %7d %20d %13d %10c \n", i, f->pid, f->frag, non_avail);
            // printf("\n");
        }
    }
}

int compare(int *a, int *b)
{
  short int toReturn = 0;
  if (*a < *b)
    toReturn = -1;
  else if (*a > *b)
    toReturn = 1;
  return toReturn;
}