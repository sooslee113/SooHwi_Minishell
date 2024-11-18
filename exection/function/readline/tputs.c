#include <stdio.h>
#include <term.h>
#include <stdlib.h>

int main() {
    char *termtype = getenv("TERM");
    char buf[1024];

    if (tgetent(buf, termtype) == 1) {
        // 커서를 10번째 행, 20번째 열로 이동하는 문자열 가져오기
        char *move_cursor = tgetstr("cm", NULL);
        if (move_cursor != NULL) {
            // 커서 이동 문자열을 tputs로 출력
            tputs(move_cursor, 1, putchar);  // 커서를 10, 20 위치로 이동
        }
    } else {
        printf("Failed to retrieve terminal information.\n");
    }

    return 0;
}