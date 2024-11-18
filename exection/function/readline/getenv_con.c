#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *home = getenv("HOME");

    if (home) {
        if (chdir(home) == 0) {  // HOME 환경 변수에 설정된 디렉토리로 이동
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("Changed directory to %s\n", cwd);
            } else {
                perror("getcwd");
            }
        } else {
            perror("chdir");
        }
    }

    return 0;
}
