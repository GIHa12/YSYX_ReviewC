#include "stack.h"
#include <stdio.h>
 
// 初始化栈
void STInit(ST* ps)
{
	assert(ps); // 这里一定要断言，如果是空指针的话，就无法找到整个数组 
 
	ps->a = NULL;
	ps->capacity = 0;
	// 这里需要注意的是当 top=0 时指向的是栈顶元素的下一个位置
	//                   top=-1 时指向的是栈顶元素
	// 这里也可以理解为顺序表中 size 有效数据的意思
	ps->top = 0;
}
 
// 栈的销毁
void STDestory(ST* ps)
{
	assert(ps);
	free(ps->a);
	ps->a = NULL;
	ps->capacity = ps->top = 0;
}
 
// 栈的尾插
void STPush(ST* ps, STDataType x)
{
	// 此时需要保证传入的栈，不是空
	assert(ps);
 
	// 扩容
	// 判断是否需要扩容
	if (ps->top == ps->capacity)
	{
		int newcapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;
		STDataType* temp = (STDataType*)realloc(ps->a, sizeof(STDataType) * newcapacity);
		// 防止返回的是空指针
		if (temp == NULL)
		{
			perror("realloc fail!");
			exit(-1);
		}
		ps->a = temp;
		ps->capacity = newcapacity;
	}
	// 进行尾插数据
	ps->a[ps->top] = x;
	ps->top++;
}
 
// 栈的删除
void STPop(ST* ps)
{
	assert(ps);
	// 只需要删除栈顶的数据即可
 
	// 需要判断栈内是否还有数据
	assert(ps->top > 0);
	ps->top--;
 
}
 
// 栈内数据的个数
int STSize(ST* ps)
{
	assert(ps);
 
	return ps->top;
}
 
// 判断栈是否为空
bool STEmpty(ST* ps)
{
	assert(ps);
 
	return ps->top == 0;
}
 
// 打印栈
void STPrint(ST* ps)
{
	assert(ps);
 
	while (!STEmpty(ps))
	{
		// 打印栈顶
		printf("%d ", STTop(ps));
		// 一边出数据一边删数据（满足后进先出）
		STPop(ps);
	}
	printf("\n");
}
 
// 获取栈顶元素
STDataType STTop(ST* ps)
{
	assert(ps);
	assert(ps->top > 0);
 
	return ps->a[ps->top - 1];
}