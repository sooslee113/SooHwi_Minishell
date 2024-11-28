#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h> 

int main() {
    pid_t pid;
    int status;
    struct rusage usage;

    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // 자식 프로세스
        printf("Child process: PID=%d\n", getpid());
        sleep(2);  // 2초 대기 후 종료
        exit(0);
    } else {
        // 부모 프로세스
        printf("Parent process: waiting for child\n");
        pid_t child_pid = wait3(&status, 0, &usage);  // 자식 프로세스의 종료 상태 및 리소스 정보 받기
        
        if (child_pid == -1) {
            perror("wait3 failed");
            exit(1);
        }

        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }

        // 자식 프로세스가 사용한 리소스 정보 출력
        printf("Child used %ld user time and %ld system time\n", usage.ru_utime.tv_sec, usage.ru_stime.tv_sec);
    }

    return 0;
}
