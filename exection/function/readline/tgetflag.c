
#include <stdio.h>
#include <term.h>
#include <stdlib.h>
int main()
{
    char *termtype = getenv("TERM");  // 환경 변수 TERM에서 터미널 타입 얻기
    char buf[1024];  // 터미널 정보를 저장할 버퍼

    // 터미널 정보 검색
    if (tgetent(buf, termtype) == 1) {
        // "colors"가 지원되는지 확인
        int color_flag = tgetflag("colors");
        if (color_flag == 1) {
            printf("This terminal supports color output.\n");
        } else {
            printf("This terminal does not support color output.\n");
        }
    } else {
        printf("Failed to retrieve terminal information.\n");
        return 1;
    }

    return 0;
}

