#include <stdio.h>
#include <term.h>
#include <stdlib.h>

int main() 
{
    char *termtype = getenv("TERM");  // 환경 변수 TERM에서 터미널 타입 얻기
    char buf[1024];  // 터미널 정보를 저장할 버퍼

    // 터미널 정보 검색
    if (tgetent(buf, termtype) == 1) {
        printf("Terminal type: %s\n", termtype);
    } else {
        printf("Failed to retrieve terminal information.\n");
        return 1;
    }

    return 0;
}

