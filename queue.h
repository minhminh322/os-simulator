#ifndef QUEUE_H
#define QUEUE_H

#include "listADTgen.h"

typedef ListType Queue;

#define queue_create(queue, compare) create(queue, compare)

#define queue_destroy(queue) destroy(queue)

#define queue_enqueue(queue, item) push(queue, item)

#define queue_dequeue(queue) removeAtIndex(queue, 0)

#define queue_size(queue) size_is(queue)

#define queue_is_empty(queue) is_empty(queue)

#define queue_print(queue) printl(queue, printItem)

#endif
