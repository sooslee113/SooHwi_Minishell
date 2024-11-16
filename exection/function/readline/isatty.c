#include <stdio.h>
#include <unistd.h>

int main() 
{
    if (isatty(STDIN_FILENO)) {
        printf("Standard input is a terminal.\n");
    } 
    else 
    {
        printf("Standard input is not a terminal.\n");
    }

    if (isatty(STDOUT_FILENO)) {
        printf("Standard output is a terminal.\n");
    } 
    else 
    {
        printf("Standard output is not a terminal.\n");
    }
    return 0;
}