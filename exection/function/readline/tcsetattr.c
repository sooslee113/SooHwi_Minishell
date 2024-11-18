
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
int main() {
    struct termios term;

    // 터미널 속성 얻기
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("tcgetattr");
        return 1;
    }

    // 현재 터미널 속성 출력
    printf("Before: c_lflag = %ld\n", term.c_lflag);

    // 터미널 설정 변경: 에코 모드 비활성화 (입력한 문자를 화면에 표시하지 않음)
    term.c_lflag &= ~ECHO;

    // 설정을 즉시 적용
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) {
        perror("tcsetattr");
        return 1;
    }

    // 터미널 속성 변경 후 확인
    printf("After: c_lflag = %ld\n", term.c_lflag);

    return 0;
}