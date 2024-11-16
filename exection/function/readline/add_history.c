#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main() {
    char *input;

    while ((input = readline("shell> ")) != NULL) {
        if (input && *input) {
            add_history(input);  // 사용자가 입력한 내용을 히스토리에 추가
        }

        printf("You entered: %s\n", input);
        free(input);
    }

    return 0;
}