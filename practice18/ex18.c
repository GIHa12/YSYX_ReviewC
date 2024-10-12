#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17. */
void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

// a typedef creates a fake type, in this
// case for a function pointer
typedef int (*compare_cb)(int a, int b); 
//只要符合原型 int function(int a ,int b)即可使用compare_cb函数指针指代
typedef int* (*sort_algorithm)(int *numbers,int count ,compare_cb cmp);
/**
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting.
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)//冒泡排序
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if(!target) die("Memory error.");
    memcpy(target, numbers, count * sizeof(int));

    for(i = 0;i<count;i++)
    {
        for(j = 0;j<count -1;j++)
        {
            if(cmp(target[j],target[j+1])>0)
            {
                temp = target[j];
                target[j] = target[j+1];
                target[j+1] = temp;
            }
        }
    }
    return target;
}

int *select_sort(int *numbers, int count, compare_cb cmp)//选择排序
{
    int temp = 0;
    int index = 0;
    int *target = malloc(count * sizeof(int));

    if(!target) die("Memory error.");
    memcpy(target, numbers, count * sizeof(int));
    
    for(int i = 0; i < count; i++) 
    {
        index = i;
        for(int j = i+1; j < count; j++) 
        {
            if(cmp(target[j], target[index]) > 0) 
            {
                index = j;
            }
        }
        if(index != i)
        {
            temp = target[i];
            target[i] = target[index];
            target[index] = temp;
        }

    }

    return target;

}

int *insert_sort(int *numbers, int count, compare_cb cmp)//插入排序
{
    int *target = malloc(count * sizeof(int));
    if(!target) die("Memory error.");
    memcpy(target, numbers, count * sizeof(int));
    for(int i = 1;i<count;i++)
    {
        int j;
        if(cmp(target[i],target[i-1])<0)
        {
            int temp = target[i];
            for(j = i-1;j>=0 && cmp(temp,target[j])<0;j--)
            {
                target[j+1] = target[j];
            }
            target[j+1] = temp;
        }
    }
    return target;

}

int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if(a == 0 || b == 0) {
        return 0;
    } else {
        return a % b;
    }
}

/**
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */
void test_sorting(int *numbers, int count, compare_cb cmp,sort_algorithm sort_function)
{
    int i = 0;
    int *sorted = sort_function(numbers, count, cmp);

    if(!sorted) die("Failed to sort as requested.");

    for(i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    free(sorted);
    unsigned char *data = (unsigned char *)cmp;

    for(i = 0; i < 50; i++) {
        printf("%02x:", data[i]); //打印函数原始的汇编字节码
    }

    printf("\n");
}

char error_sorting(int a,int b)
{
    return '1';
}

int main(int argc, char *argv[])
{
    if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if(!numbers) die("Memory error.");

    for(i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]); //char ->int
    }

    test_sorting(numbers, count, sorted_order,bubble_sort);
    test_sorting(numbers, count, reverse_order,insert_sort);
    test_sorting(numbers, count, strange_order,insert_sort);
    // test_sorting(numbers, count, NULL);

    free(numbers);

    return 0;
}