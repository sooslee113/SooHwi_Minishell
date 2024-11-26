#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
int main() {
    int fd = open("/dev/tty", O_RDWR);  // 터미널 장치 열기
    struct termios term;

    if (fd == -1) {
        perror("Failed to open terminal");
        return 1;
    }

    // 터미널 속성 가져오기
    if (ioctl(fd, TCGETS, &term) == -1) {
        perror("ioctl failed");
        close(fd);
        return 1;
    }

    // 여기서 term 구조체의 값을 수정할 수 있음 (예: 터미널 모드 변경)

    close(fd);
    return 0;
}