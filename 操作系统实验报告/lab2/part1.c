#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 1024
char fibonacci_string[SIZE];


void get_fibonacci(void *n) {
    int num = *((int *)n);
    printf("thread begins!\n");
    if (num == 1) {
        sprintf(fibonacci_string, "%d", 0);
    }
    else {
        sprintf(fibonacci_string, "%d %d", 0, 1);
        int fib0 = 0, fib1 = 1;
        for (int i = 0; i < num; i++) {
            int fibonacci_string_length = strlen(fibonacci_string);
            if (i % 2 == 0) {
                fib0 += fib1;
                sprintf(fibonacci_string + fibonacci_string_length, " %d", fib0);
            }
            else {
                fib1 += fib0;
                sprintf(fibonacci_string + fibonacci_string_length, " %d", fib1);
            }
        }
    }
    int fibonacci_string_length = strlen(fibonacci_string);
    sprintf(fibonacci_string + fibonacci_string_length, "\n");
}

void print_error_message() {
    printf("Please input a positive number\n");
    exit(1);
}

int main(int argv, char* args[]) {
    if (argv != 2) {
        print_error_message();
    }

    for (int i = 0; i < strlen(args[1]); i++) {
        if (!isdigit(args[1][i]))
            print_error_message();
    }

    int num = atoi(args[1]);
    if (num == 0)
        print_error_message();
    
    pthread_t thread;
    if (pthread_create(&thread, NULL, (void *)&get_fibonacci, (void *)&num) != 0) {
        printf("create thread fail.\n");
        exit(1);
    }

    void *retival;
    if (pthread_join(thread, &retival) != 0)
        printf("cannot join with thread\n");
    else
        printf("thread is end!\n");

    printf("%s\n", fibonacci_string);
    printf("Done!\n");

    exit(0);
    
}
