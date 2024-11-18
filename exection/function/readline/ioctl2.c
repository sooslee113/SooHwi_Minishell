#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

struct winsize w;

int main() {
    // 현재 터미널 크기 가져오기
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("ioctl failed");
        return 1;
    }

    printf("Terminal size: %d rows, %d columns\n", w.ws_row, w.ws_col);
    return 0;
}