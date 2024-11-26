#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

// 파이프 생성 함수
void making_pipe(int num_pipes, int fd[][2])
{
    int i;

    i = 0;
    while(i < num_pipes)
    {
        if (pipe(fd[i]) < 0)
        {
            perror("pipe error");
            exit(1);
        }
        i ++;
    }
}
int main(int argc, char **argv, char **envp)
{
    if (argc == 1)
    {
        printf("Usage: %s <commands>\n", argv[0]);
        return 1;
    }

    int num_pipes = argc - 2; // 파이프 개수는 (명령어 수 - 1)
    int fd[num_pipes][2];     // 파이프 배열
    int pid[argc - 1];        // 프로세스 배열
	char *path;
    // 파이프 생성
    making_pipe(num_pipes, fd);

    // 각 명령어에 대해 프로세스 생성
    for (int i = 0; i < argc - 1; i++)
    {
        pid[i] = fork(); // 프로세스 생성

        if (pid[i] == 0) // 자식 프로세스
        {
            // 입력 리다이렉션 설정
            if (i > 0) // 첫 번째 프로세스가 아니라면
                dup2(fd[i - 1][0], STDIN_FILENO); // 이전 파이프의 읽기 끝을 표준 입력으로 연결
            // 출력 리다이렉션 설정
            if (i < num_pipes) // 마지막 프로세스가 아니라면
                dup2(fd[i][1], STDOUT_FILENO); // 현재 파이프의 쓰기 끝을 표준 출력으로 연결
            // 모든 파이프 닫기
            for (int j = 0; j < num_pipes; j++)
            {
                close(fd[j][0]);
                close(fd[j][1]);
            }
            // 명령어 실행
            execlp(argv[i + 1], argv[i + 1], NULL);
            printf("%s is error\n", argv[i + 1]);
            perror("exec error"); // exec 실패 시 오류 출력
            exit(1);
        }
    }

    // 부모 프로세스: 모든 파이프 닫기
    for (int i = 0; i < num_pipes; i++)
    {
        close(fd[i][0]);
        close(fd[i][1]);
    }

    // 모든 자식 프로세스 대기
    for (int i = 0; i < argc - 1; i++)
    {
        waitpid(pid[i], NULL, 0);
    }

    return 0;
}
