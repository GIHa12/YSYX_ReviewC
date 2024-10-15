#ifndef lcthw_queue_h
#define lcthw_queue_h
#include <lcthw/list.h>
typedef List Queue; 

#define Queue_create() List_create()
#define Queue_destroy(queue) List_destroy(queue)
#define Queue_send(queue,value) List_push(queue,value) //尾插
#define Queue_peek(queue) List_first(queue) //查看第一个元素？
#define Queue_count(queue) List_count(queue)
#define Queue_recv(queue) List_shift(queue)
#define QUEUE_FOREACH(queue, cur) LIST_FOREACH(queue,last,next,cur)


#endif