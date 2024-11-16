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
        char *move_cursor = tgetstr("cm", NULL);  // "cm"은 커서 이동 명령을 반환

        if (move_cursor != NULL) {
            // 커서를 10번째 행, 20번째 열로 이동
            tputs(tgoto(move_cursor, 10, 20), 1, putchar);  // tputs와 tgoto를 사용하여 커서를 이동
        } else {
            printf("Failed to retrieve move cursor command.\n");
        }
    } else {
        printf("Failed to retrieve terminal information.\n");
        return 1;
    }

    return 0;
}
