#include <stdio.h>
#include <term.h>
#include <stdlib.h>

int main() 
{
    char *termtype = getenv("TERM");  // 환경 변수 TERM에서 터미널 타입 얻기
    char buf[1024];  // 터미널 정보를 저장할 버퍼

    // 터미널 정보 검색
    if (tgetent(buf, termtype) == 1) {
        // 커서 이동 명령 "cm" 가져오기
        char *move_cursor = tgetstr("cm", NULL);
        
        if (move_cursor != NULL) {
            // (5, 10)으로 커서를 이동
            char *cursor_move = tgoto(move_cursor, 10, 5); // 10번째 열, 5번째 행
            printf("%s", cursor_move);
            printf("Cursor moved to position (10, 5)\n");
        } else {
            printf("Failed to retrieve move cursor command.\n");
        }
    } else {
        printf("Failed to retrieve terminal information.\n");
        return 1;
    }

    return 0;
}