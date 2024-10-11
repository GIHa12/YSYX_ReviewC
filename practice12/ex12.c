#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    if(argc == 1) {
        printf("You only have one argument. You suck.\n");
    } else if(argc > 1 && argc < 4) { //若将逻辑改为或则成了并集，表示的范围为除了第一个if表示的1个参数外，其余任意个参数都会输出
        printf("Here's your arguments:\n");

        for(i = 0; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    } //注释掉else之后将看不到4个参数以外情况的输出
    else {
        printf("You have too many arguments. You suck.\n");
    }

    return 0;
}