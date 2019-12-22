#ifndef PARTITION_H
#define PARTITION_H

typedef struct frame_t *Frame;
typedef struct partition_table_t *Partition;

int compare(int *, int *);
 
Frame create_frame(short thePid, int theFrag);
Partition create_partition_list(int partition_num);

void add_partition(Partition pptr, short thePid, int theFrag, int *frame_index);
void delete_partition(Partition pptr, int del_index);

void frame_destroy(Frame fptr);
void partition_list_destroy(Partition pptr);

void print_partition_table(Partition pptr, int par_num);

#endif