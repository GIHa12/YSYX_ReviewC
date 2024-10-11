#include <stdio.h>

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("ERROR: You need one argument.\n");
        // this is how you abort a program
        return 1;
    }

    int i = 0;
    char letter=argv[1][i];
    for(i = 0; argv[1][i] != '\0'; i++,letter = argv[1][i]) 
    {
        if(letter>='a' && letter <='z')
        {
            argv[1][i] = argv[1][i]-32;
        }
        if(letter>='A' && letter <='Z')
        {
            argv[1][i] = ' ';
        }
    }
    printf("%s\n",argv[1]);

    return 0;
}