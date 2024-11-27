#include <stdio.h>
#include <unistd.h>

int main() {
    if (unlink("unlink_example.txt") == -1) {
        perror("Failed to delete file");
        return 1;
    }
    printf("File deleted successfully\n");
    return 0;
}