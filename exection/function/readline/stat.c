#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    struct stat fileStat;
    
    // 파일의 상태 정보 얻기
    if (stat("stat_example.txt", &fileStat) == -1) {
        perror("stat failed");
        return 1;
    }

    // 파일 정보 출력
    printf("File size: %ld bytes\n", fileStat.st_size);
    printf("Last access time: %ld\n", fileStat.st_atime);
    printf("Last modification time: %ld\n", fileStat.st_mtime);
    printf("File permissions: %o\n", fileStat.st_mode & 0777); // 파일 권한을 8진수로 출력

    return 0;
}