#ifndef lcthw_stack_h
#define lcthw_stack_h
#include <lcthw/list.h>
typedef List Stack;
#define Stack_create() List_create()
#define Stack_destroy(stack) List_destroy(stack)
#define Stack_push(stack,value) List_push(stack,value) //压栈
#define Stack_peek(stack) List_last(stack) //查看栈顶元素
#define Stack_pop(stack) List_pop(stack)
#define Stack_count(stack) List_count(stack)
#define STACK_FOREACH(stack,cur) LIST_FOREACH(stack,last,prev,cur)
#endif