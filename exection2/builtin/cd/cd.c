
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    // 현재 디렉터리 출력
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current directory: %s\n", cwd);
    } else {
        perror("getcwd failed");
        return 1;
    }

    // 디렉터리 변경
    if (chdir("/home/user/projects") == 0) {
        // 변경 후 디렉터리 출력
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Changed directory to: %s\n", cwd);
        } else {
            perror("getcwd failed after chdir");
            return 1;
        }
    } else {
        perror("chdir failed");
        return 1;
    }

    return 0;
}