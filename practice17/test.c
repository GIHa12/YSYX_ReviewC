
#include "stack.h"
#include <stdio.h>
 
 
// 尾插测试
void Test1()
{
	// 定义一个结构体变量
	// 要改变这个结构体变量，就要在形参上 传递 结构体变量的地址
	ST ps;
	// 进行初始化
	STInit(&ps);
	// 将结构体变量的地址给给尾插函数
	printf("********************测试队列*****************\n");
	printf("\n");
	printf("********************进行尾插*****************\n");
	printf("\n");
	printf("********************尾插1 2 3 4 5\n");
	printf("\n");
	STPush(&ps, 1);
	STPush(&ps, 2);
	STPush(&ps, 3);
	STPush(&ps, 4);
	STPush(&ps, 5);
	printf("****输出（满足后进先出原则）\n");
	printf("\n");
	STPrint(&ps);
	
 
	// 销毁（防止内存泄露）
	STDestory(&ps);
}
 
 
// 尾删测试
void Test2()
{
	// 定义一个结构体变量
	ST ps;
	// 进行初始化
	STInit(&ps);
	// 将结构体变量的地址给给尾插函数
	STPush(&ps, 1);
	STPush(&ps, 1);
	STPush(&ps, 1);
 
	STPop(&ps);
	STPrint(&ps);
 
	// 销毁（防止内存泄露）
	STDestory(&ps);
}
 
 
 
int main()
{
	Test1();
	return 0;
}
