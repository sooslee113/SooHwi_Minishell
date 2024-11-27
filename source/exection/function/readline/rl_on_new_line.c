#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h> 

// 신호 핸들러 - 예: Ctrl+C 시 현재 라인을 재설정
void handle_sigint(int signum) {
    rl_on_new_line();        // 새로운 라인 준비
    rl_replace_line("", 0);  // 현재 줄을 빈 문자열로 대체
    rl_redisplay();          // 화면에 업데이트
}

int main() {
    char *input;

    // SIGINT 핸들러 설정
    signal(SIGINT, handle_sigint);

    while ((input = readline("Enter command: ")) != NULL) {
        if (*input) {
            add_history(input);
        }
        printf("You entered: %s\n", input);
        free(input);
    }

    return 0;
}
