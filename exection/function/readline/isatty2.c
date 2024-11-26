#include <stdio.h>
#include <unistd.h>

int main() {
    if (isatty(STDIN_FILENO)) 
    {
        printf("Interactive mode: Enter your command\n");
        char command[100];
        fgets(command, sizeof(command), stdin);
        printf("You entered: %s", command);
    } 
    else 
    {
        printf("Non-interactive mode: Reading input from a file or pipe\n");
    }
    return 0;
}