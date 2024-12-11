#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
    char *tty;

    int fd;

    fd = open("ttyname.txt", O_RDONLY);
    // ttyname 함수로 표준 입력이 연결된 터미널 장치의 경로 확인
    tty = ttyname(fd);

    if (tty != NULL) {
        printf("Standard input is connected to terminal: %s\n", tty);
    } else {
        printf("Standard input is not connected to a terminal.\n");
    }

    return 0;
}