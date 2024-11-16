#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>

int main() 
{
    char *input;

    while ((input = readline("shell> ")) != NULL) {
        if (strcmp(input, "hello") == 0) {
            rl_replace_line("Hello, World!", 0); // "hello"를 "Hello, World!"로 대체
            rl_redisplay();                     // 변경된 입력 줄을 표시
        }
        else
          printf("\nYou entered: %s\n", input);
        free(input);
    }
    return 0;
}