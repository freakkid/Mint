#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define M 3
#define K 2
#define N 3

int A[M][K] = {{1, 4}, {2, 5}, {3, 6}};
int B[K][N] = {{8, 7, 6}, {5, 4, 3}};
int C[M][N];

struct para {
    int i;
    int j;
};

void calcultate_new_matrix(void *pa) {
    struct para *p = (struct para *)pa;
    int i = p->i;
    int j = p->j;
    C[i][j] = 0;
    for (int k = 0; k < K; k++) {
        C[i][j] += A[i][k] * B[k][j];
    }
}

int main() {
    pthread_t thread[M][N];
    struct para pa[M][N];

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            pa[i][j].i = i;
            pa[i][j].j = j;
            if (pthread_create(&thread[i][j], NULL, (void *)&calcultate_new_matrix, (void *)&pa[i][j]) != 0) {
                printf("create thread[%d][%d] fail.\n", i, j);
                exit(1);
            }
        }
    }

    void *retival;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (pthread_join(thread[i][j], &retival) != 0)
                printf("cannot join with thread\n");
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        putchar('\n');
    }

    return 0;
}