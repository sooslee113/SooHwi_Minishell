#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main() 
{
    int fd = open("fstat_example.txt", O_RDONLY);  // 파일을 읽기 전용으로 엽니다.
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    struct stat buf;
    if (fstat(fd, &buf) == -1) {
        perror("fstat failed");
        close(fd);
        return 1;
    }

    // 파일 정보 출력
    printf("File size: %ld bytes\n", buf.st_size);
    printf("Last modified: %ld\n", buf.st_mtime);
    printf("File permissions: %o\n", buf.st_mode & 0777);
    printf("Number of links: %ld\n", buf.st_nlink);

    close(fd);
    return 0;
}