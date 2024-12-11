#include <stdio.h>
#include <term.h>
#include <stdlib.h>

int main()
{
    char *termtype = getenv("TERM");  // 환경 변수 TERM에서 터미널 타입 얻기
    char buf[1024];  // 터미널 정보를 저장할 버퍼

    // 터미널 정보 검색
    if (tgetent(buf, termtype) == 1) {
        // 커서 이동 명령 얻기
        char *move_cursor = tgetstr("cm", NULL);

        if (move_cursor != NULL) {
            // 커서를 10번째 행, 20번째 열로 이동
            printf("Move cursor command: ");
            tputs(move_cursor, 1, putchar);  // tputs로 출력하여 커서를 이동시킴
            // 실제로 커서를 이동시키기 위해서는 다음과 같이 해야 합니다.
            printf("\033[10;20H");  // 커서를 10, 20으로 이동
        } else {
            printf("Failed to retrieve move cursor command.\n");
        }
    } else {
        printf("Failed to retrieve terminal information.\n");
        return 1;
    }

    return 0;
}