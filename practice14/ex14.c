#include <stdio.h>
#include <ctype.h>
#include <string.h>

void print_arguments(int argc, char *argv[],int maxlength)
{
    int i = 0;

    for(i = 0; i < argc; i++) 
    {
        for(int j = 0; argv[i][j] != '\0'&& j<maxlength; j++) 
        {
            char ch = argv[i][j];

            if(isalpha(ch) || isblank(ch)) 
            {
                printf("'%c' == %d ", ch, ch);
            }
        }

        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int maxlength = 3;
    print_arguments(argc, argv,maxlength);
    return 0;
}
