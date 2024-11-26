
#include <stdio.h>
#include <unistd.h>
int main() {
    int slot = ttyslot();

    if (slot == -1) {
        perror("ttyslot failed");
    } else {
        printf("This process is running on terminal slot: %d\n", slot);
    }

    return 0;
}