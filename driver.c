// This program runs on Ubuntu 16.04 Linux VM.

#include <stdio.h>
#include <stdlib.h>
#include "listADTgen.h"
#include "partition.h"
#include "process.h"
#include "queue.h"

int main(void)
{
  Partition partition_table_list;
  Processtable process_table_list;
  Queue queue_partition_avail;

  int par_num, frame_size, user_choice = 0, process_size, process_id_del;

  printf("Enter the number of partitions: ");
  scanf("%d", &par_num);

  printf("Enter the size of each partition: ");
  scanf("%d", &frame_size);

  /* Create partition and Process table. */
  partition_table_list = create_partition_list(par_num);
  process_table_list = create_process_table_list();
  /* Queue list to keep track of available partitions. */
  queue_partition_avail = queue_create(sizeof(int), NULL);

  int pid_counter = 1;
  int queue_counter = 0;

  int *current_frame_queue;
  int i;

  /* Create a queue to keep track of available partitions. */
  for (i = 0; i < par_num; i++)
  {
    queue_enqueue(queue_partition_avail, &i);
  }

  /* Prompt user choices */
  while (user_choice != 4)
  {

    printf("Do you want to: \n");
    printf("Add a process? Enter 1\n");
    printf("Delete a process? Enter 2\n");
    printf("Print values? Enter 3\n");
    printf("Quit? Enter 4\n");
    scanf("%d", &user_choice);

    if (user_choice == 1)
    {
      printf("Adding - enter process size: ");
      scanf("%d", &process_size);
      // Calculate the size of process.
      int calc_size, divide, diff_num;
      calc_size = frame_size - process_size;
      diff_num = process_size;
      divide = process_size / frame_size;

      if (queue_size(queue_partition_avail) < (divide + 1))
      {
        printf("RAM is full");
        break;
      }

      if (calc_size >= 0)
      {
        current_frame_queue = (int *)queue_dequeue(queue_partition_avail);

        // Add a new partition
        add_partition(partition_table_list, pid_counter, calc_size, current_frame_queue);

        // Add a new process
        add_process(process_table_list, pid_counter, process_size);
        add_frame_queue(process_table_list, queue_counter, current_frame_queue);

        free(current_frame_queue);
      }

      if (calc_size < 0)
      {
        // Add a new process
        add_process(process_table_list, pid_counter, process_size);

        for (i = 0; i < divide; i++)
        {
          current_frame_queue = (int *)queue_dequeue(queue_partition_avail);
          // Work with full partition
          add_partition(partition_table_list, pid_counter, 0, current_frame_queue);
          add_frame_queue(process_table_list, queue_counter, current_frame_queue);
          diff_num -= frame_size;
          free(current_frame_queue);
        }
        current_frame_queue = (int *)queue_dequeue(queue_partition_avail);
        // Add the rest of fragmentation into last partition
        add_partition(partition_table_list, pid_counter, diff_num, current_frame_queue);
        add_frame_queue(process_table_list, queue_counter, current_frame_queue);

        free(current_frame_queue);
      }
      pid_counter++;
      queue_counter++;
    }

    if (user_choice == 2)
    {
      printf("Deleting - enter process id: ");
      scanf("%d", &process_id_del);

      int process_index = get_frame_index(process_table_list, process_id_del);
      int queue_size = get_queue_size(process_table_list, process_index);

      // Delete in partition table
      int *process_frame_dequeue;
      for (i = 0; i < queue_size; i++)
      {
        process_frame_dequeue = get_queue_frame(process_table_list, process_index);
        queue_enqueue(queue_partition_avail, process_frame_dequeue);
        delete_partition(partition_table_list, *process_frame_dequeue);
        free(process_frame_dequeue);
      }
      // Delete in process table
      delete_process(process_table_list, process_index);
      queue_counter--;
    }

    if (user_choice == 3)
    {
      printf("Printing -\n------------------------------------------------------------\n");
      printf("Process Table: \n");
      printf("Process id              Frames:\n");
      print_process_table(process_table_list);
      printf("------------------------------------------------------------\n");
      printf("Partition Table: \n");
      printf("Partition number        Process id      Frag    Availability\n");
      print_partition_table(partition_table_list, par_num);
      printf("------------------------------------------------------------\n");
    }
  }

  partition_list_destroy(partition_table_list);
  process_list_destroy(process_table_list);
  destroy(queue_partition_avail);

  return 0;
}
