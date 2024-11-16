#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("opendir failed");
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);  // 파일 이름 출력
    }

    closedir(dir);  // 디렉터리 스트림 닫기
    return EXIT_SUCCESS;
}
