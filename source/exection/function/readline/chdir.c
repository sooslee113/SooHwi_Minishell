#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    char path[1024];
    
    // 사용자로부터 디렉터리 경로 입력 받기
    printf("Enter directory path: ");
    fgets(path, sizeof(path), stdin);
    
    // 입력 받은 경로에서 개행 문자 제거
    path[strcspn(path, "\n")] = '\0';
    
    // 디렉터리 변경
    if (chdir(path) == 0) {
        printf("Changed to directory: %s\n", path);
    } else {
        perror("chdir failed");
    }

    return 0;
}
