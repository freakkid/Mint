#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int pid1 = fork();
    if (pid1 != 0) {
        int pid2 = fork();
        if (pid2 != 0)
            printf("a\n");
        else
            printf("b\n");
    }
    else {
        printf("b\n");
    }
}