#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main() {
    const char *dir_path = "./";  // 현재 디렉터리를 예로 사용
    DIR *dir = opendir(dir_path); // 디렉터리 열기

    if (dir == NULL) {
        perror("opendir failed");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name); // 디렉터리 내 파일/폴더 이름 출력
    }

    closedir(dir); // 디렉터리 닫기
    return 0;
}