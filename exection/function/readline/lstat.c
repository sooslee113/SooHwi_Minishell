
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() 
{
    struct stat fileStat;

    // 심볼릭 링크에 대한 상태 정보 조회
    if (lstat("example_link_lstat", &fileStat) == -1) {
        perror("lstat failed");
        return 1;
    }

    // 심볼릭 링크가 파일인지 확인
    if (S_ISLNK(fileStat.st_mode)) {
        printf("It's a symbolic link.\n");
    } else {
        printf("It's not a symbolic link.\n");
    }

    return 0;
}

