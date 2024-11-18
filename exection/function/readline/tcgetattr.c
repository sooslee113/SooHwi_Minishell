#include <termios.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    struct termios term;

    // 현재 터미널 속성 읽기
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("tcgetattr");
        return 1;
    }

    // ECHO 모드 비활성화 (입력한 문자가 화면에 표시되지 않도록)
    term.c_lflag &= ~ECHO;

    // 변경된 속성 설정
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) {
        perror("tcsetattr");
        return 1;
    }

    printf("ECHO mode disabled. Type something (input won't be displayed): ");
    getchar();  // 사용자가 입력한 문자는 화면에 표시되지 않음

    return 0;
}