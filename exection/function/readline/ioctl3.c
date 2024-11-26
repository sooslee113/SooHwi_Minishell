#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

int main() {
    int fd = open("/dev/sda", O_RDONLY);  // 블록 장치 파일 열기
    unsigned long size;

    if (fd == -1) {
        perror("Failed to open device");
        return 1;
    }

    // 장치의 물리적 크기 확인
    if (ioctl(fd, BLKGETSIZE, &size) == -1) {
        perror("ioctl failed");
        close(fd);
        return 1;
    }

    printf("Device size: %lu bytes\n", size);
    close(fd);
    return 0;
}