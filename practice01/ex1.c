#include <stdio.h>
int main(int argc, char *argv[])
{
	puts("Hello World.");
    puts("你好！");
    puts("\"Hello World\"");
    puts("123|[]");
    puts("+_)(*&^%$#@!)");
    FILE *p = fopen("./test.txt","r+");
    fputs("123\n",p); //从文件写指针指定位置开始写字符串，没有自带分号分隔
    fputc('a',p);  //写字符
    return 0;
}
