#ifndef PROCESS_H
#define PROCESS_H

typedef struct process_t *Process;
typedef struct process_table_t *Processtable;

void printItem(int *);
 
Process create_process(unsigned short thePid, unsigned int theSize);
Processtable create_process_table_list();

void add_process(Processtable ptptr, unsigned short thePid, unsigned int theSize);
void add_frame_queue(Processtable ptptr, int queue_counter, int *frame_queue); 
int *get_queue_frame(Processtable ptptr, int frame_index);
int get_frame_index(Processtable ptptr, int process_id);
int get_queue_size(Processtable ptptr, int frame_index);
void delete_process(Processtable ptptr, int process_index);

void process_list_destroy(Processtable ptptr);

void print_process_table(Processtable procptr);

#endif