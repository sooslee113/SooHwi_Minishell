#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// SIGINT 시그널을 처리할 핸들러 함수
void handle_sigint(int sig) {
    printf("\nCaught SIGINT (signal number %d)\n", sig);
}

int main() {
    struct sigaction act;

    act.sa_handler = handle_sigint;    // SIGINT 발생 시 handle_sigint 핸들러 호출
    sigemptyset(&act.sa_mask);         // sa_mask를 빈 집합으로 초기화
    sigaddset(&act.sa_mask, SIGQUIT);  // SIGQUIT 시그널을 sa_mask에 추가
    act.sa_flags = 0;

    // SIGINT에 대한 새로운 동작을 설정
    if (sigaction(SIGINT, &act, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Press Ctrl+C (SIGINT) to trigger the signal handler.\n");
    printf("Press Ctrl+\\ (SIGQUIT) will be blocked during SIGINT handling.\n");

    while (1) {
        printf("Running... (press Ctrl+C or Ctrl+\\)\n");
        sleep(2);
    }

    return 0;
}