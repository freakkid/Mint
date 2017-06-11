#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define SIZE 1024
extern int errno;       // linux下捕获错误

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./a.out [number]\n");
        exit(1);
    }

    for (int i = 0; i < strlen(argv[1]); i++) {
        if (!isdigit(argv[1][i])) {
            printf("Please enter a positive number!\n");
            exit(1);
        }
    }

    int num = atoi(argv[1]);
    if (num == 0) {
        printf("Please enter a positive number!\n");
        exit(1);
    }

    int shmid;
    char *shmptr;
    key_t key;
    // 生成一个整数IPC，确保父子进程的ICP相同
    if ((key = ftok("/dev/null", 1)) < 0) {
        printf("ftok error:%s\n", strerror(errno));
        return -1;
    }
    // 创建一个新的IPC对象
    if ((shmid = shmget(key, SIZE, 0600|IPC_CREAT|IPC_EXCL)) < 0) {
        printf("shmget error:%s\n", strerror(errno));
        return -1;
    }

    pid_t fork1 = fork();

    if (fork1 < 0) {
        printf("fork error:%s\n", strerror(errno));
        return -1;
    }
    else if (fork1 == 0) {
        if ((shmptr = (char*)shmat(shmid, 0, 0)) == (void*)-1) {
            printf("child shmat error:%s\n", strerror(errno));
            return -1;
        }
        
        char format_string[SIZE];
        if (num == 1) {
            sprintf(format_string, "%d", 0);
        }
        else if (num == 2) {
            sprintf(format_string, "%d %d", 0, 1);
        }
        else {
            int fib0 = 0, fib1 = 1;
            sprintf(format_string, "%d %d ", 0, 1);
            for (int i = 2; i < num; i++) {
                int format_string_length = strlen(format_string);
                if (i % 2 == 0) {
                    fib0 += fib1;
                    sprintf(format_string+format_string_length, "%d ", fib0);     
                }
                else {
                    fib1 += fib0;
                    sprintf(format_string+format_string_length, "%d ", fib1);
                }
            }
        }

        int format_string_length = strlen(format_string);
        sprintf(format_string+format_string_length, "\n");
        memcpy(shmptr, format_string, sizeof(format_string));
        puts("child Done!\n");
        exit(0);
    }
    else {        
        if ((shmptr = (char*)shmat(shmid, 0, 0)) == (void*)-1) {
            printf("parent shmat error:%s\n", strerror(errno));
            return -1;
        }
        
        wait(0);
        puts("parent Output:");
        puts(shmptr);

        if ((shmctl(shmid, IPC_RMID, 0) < 0)) {
            printf("parent shmctl error:%s\n", strerror(errno));
            return -1;
        }
        printf("parent Done!\n");
        
    }
    
}