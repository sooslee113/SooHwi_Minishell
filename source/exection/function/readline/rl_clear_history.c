#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int main() {
    char *input;

    // 입력을 받아 히스토리에 추가
    while ((input = readline("Enter something: ")) != NULL) 
    {
        if (*input) {
            add_history(input);  // 히스토리에 저장
        }
        
        // "clear" 입력 시 히스토리 삭제
        if (strcmp(input, "clear") == 0) {
            rl_clear_history();
            printf("History cleared.\n");
        } else {
            printf("You entered: %s\n", input);
        }

        free(input);  // 메모리 해제
    }
    return 0;
}
