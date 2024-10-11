#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
/*
将这个程序改为不用指针和malloc的版本。需要研究下面这些东西：
如何在栈上创建结构体，就像你创建任何其它变量那样。
如何使用x.y而不是x->y来初始化结构体。
如何不使用指针来将结构体传给其它函数。
*/
struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person Person_create(char *name, int age, int height, int weight)
{
    struct Person who = {name,age,height,weight};//若不使用malloc开辟内存，则默认将变量创建在堆栈中
    return who;
}

void Person_print(struct Person who)
{
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\tHeight: %d\n", who.height);
    printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char *argv[]) 
{
    // make two people structures
    struct Person joe = Person_create(
            "Joe Alex", 32, 64, 140);

    struct Person frank = Person_create(
            "Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", &joe);
    Person_print(joe);

    printf("Frank is at memory location %p:\n", &frank);
    Person_print(frank);

    // make everyone age 20 years and print them again
    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;
    Person_print(joe);

    frank.age += 20;
    frank.weight += 20;
    Person_print(frank);

    return 0;
}