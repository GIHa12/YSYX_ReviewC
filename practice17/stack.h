#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
 
// 静态的栈
//#define N 10
//struct Stack
//{
//	int a[N];    定义了一个指定好大小的数组
//	int size;
//};
 
 
// 动态栈
// 栈可以选择链表也可以选择数组，为什么要选择动态数组呢
// 因为数组的尾插和尾删效率比较高，而栈刚刚好，是先进后出，并且只能从一端进，一端出（栈顶）
typedef int STDataType;   // 定义数据类型
typedef struct Stack
{
	STDataType* a;   // 定义一个动态数组
	int top;  // 用来确定栈顶位置（指向栈顶元素的下一个位置）
	int capacity;  // 栈的容量
}ST;               // ST 为结构体的缩写名
 
// 初始化栈
void STInit(ST* ps);
// 栈的销毁
void STDestory(ST* ps);
 
// 栈的尾插
void STPush(ST* ps, STDataType x);
// 栈的删除
void STPop(ST* ps);
// 栈的个数
int STSize(ST* ps);
// 判断栈是否为空
bool STEmpty(ST* ps);
// 打印栈
void STPrint(ST* ps);
// 获取栈顶元素
STDataType STTop(ST* ps);