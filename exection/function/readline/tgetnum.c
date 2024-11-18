#include <stdio.h>
#include <term.h>
#include <stdlib.h>

int main() 
{
    char *termtype = getenv("TERM");  // 환경 변수 TERM에서 터미널 타입 얻기
    char buf[1024];  // 터미널 정보를 저장할 버퍼

    // 터미널 정보 검색
    if (tgetent(buf, termtype) == 1) {
        // 최대 열 수 가져오기
        int cols = tgetnum("cols");
        if (cols == -1) {
            printf("Failed to retrieve number of columns.\n");
        } else {
            printf("Terminal supports %d columns.\n", cols);
        }


  }
   return 0;
}

