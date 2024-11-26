#include <stdio.h>
#include <stdlib.h>
int main() {
    // 환경 변수 HOME의 값을 가져오기
    char *home = getenv("HOME");

    if (home != NULL) {
        printf("HOME: %s\n", home);
    } else {
        printf("HOME 환경 변수가 설정되어 있지 않습니다.\n");
    }

    // 환경 변수 PATH의 값을 가져오기
    char *path = getenv("PATH");

    if (path != NULL) {
        printf("PATH: %s\n", path);
    } else {
        printf("PATH 환경 변수가 설정되어 있지 않습니다.\n");
    }

    return 0;
}

