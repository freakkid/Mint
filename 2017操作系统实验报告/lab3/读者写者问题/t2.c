#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 10
pthread_t pthreads[THREAD_NUM];
char pthreads_flag[THREAD_NUM];
int delay_times[THREAD_NUM];
int op_times[THREAD_NUM];
int pthread_index[THREAD_NUM];    // 线程的下标，保证所有线程在运行时能正确获取自己的下标

int reader_count = 0;   // 当前读者数目
int writer_count = 0;   // 当前写者数目

// 互斥对象控制对read_count修改
static pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
// 互斥对象控制对write_count修改
static pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;
sem_t fmutex;               // 对文件获取（读或写）的互斥对象
sem_t entermutex;           // 阻塞读者进程，保证只有写者优先拿到quemutex
sem_t quemutex;             // 阻塞读者进程


void *read_file(void *param) {
    int i = *((int*)(param));
    sleep(delay_times[i]);    
    printf("%d reader is applying\n", i+1);

    // 很多读者在这里排队
    sem_wait(&entermutex);
    // 只有一个读者进入这里，保证该读者释放quemutex时，写者优先拿到quemutex    
    // 临界区
    sem_wait(&quemutex);
    // 临界区
    pthread_mutex_lock(&mutex2);
    if (reader_count == 0) {    // 等待前面的写者写完释放fmutex
        sem_wait(&fmutex);
    }
    ++reader_count;
    pthread_mutex_unlock(&mutex2);
    sem_post(&quemutex);
    sem_post(&entermutex);
    
    // read
    printf("%d reader starts reading\n", i+1);
    sleep(op_times[i]);
    printf("%d reader ends reading\n", i+1);
    
    pthread_mutex_lock(&mutex2);
    --reader_count;
    if (reader_count == 0) {    // 读者读完了，写者可以写了
        sem_post(&fmutex);      // 释放时写者优先获取fmutex
    }
    pthread_mutex_unlock(&mutex2);
    return (NULL);
}

void *write_file(void *param) {
    int i = *((int*)(param));
    sleep(delay_times[i]);    
    printf("%d writer is applying\n", i+1); 

    pthread_mutex_lock(&mutex3);
    if (writer_count == 0) {    // 等待某个读者读完释放quemutex
        sem_wait(&quemutex);
    }
    ++writer_count;
    pthread_mutex_unlock(&mutex3);
    
    // write
    sem_wait(&fmutex);
    printf("%d writer starts writing\n", i+1);
    sleep(op_times[i]);
    printf("%d writer ends writing\n", i+1);
    sem_post(&fmutex);

    pthread_mutex_lock(&mutex3);
    --writer_count;
    if (writer_count == 0) {    // 所有写者写完了，释放quemutex，让读者去读
        sem_post(&quemutex);
    }
    pthread_mutex_unlock(&mutex3);
    return (NULL);
}

void init_sems() {
    pthread_mutex_init(&mutex2, NULL);
    pthread_mutex_init(&mutex3, NULL);    
    sem_init(&fmutex, 0, 1);
    sem_init(&quemutex, 0, 1);
    sem_init(&entermutex, 0, 1);
    int i = 0;
    for (i = 0; i < THREAD_NUM; i++) {
        pthread_index[i] = i;
    }
}

int main(int argc, char *argv[]) {
    printf("writer first\n");
    // 线程序号 线程角色(R/W) 存放或取出操作的开始时间 操作持续时间
    // 判断命令行参数
    if (argc != 2) {
        printf("Usage: ./a.out [filename]\n");
        exit(0);
    }
    // 读取文件数据
    FILE *fin;
    if ((fin = fopen(argv[1], "r")) == NULL) {
        printf("Open fail\n");
        exit(1);
    }

    int r_num = 0;
    int w_num = 0;
    while (!feof(fin)) {
        int index, delay_time, op_time;
        char flag;
        fscanf(fin, "%d %c %d %d\n", &index, &flag, &delay_time, &op_time);
        pthreads_flag[index-1] = flag;
        delay_times[index-1] = delay_time;
        op_times[index-1] = op_time;
        if (flag == 'R') {
            ++r_num;
        }
        else {
            ++w_num;            
        }
    }
    fclose(fin);
    
    // 初始化信号量和随机数
    init_sems();

    // 生成读者和写者进程
    int i = 0, all_num = r_num + w_num;
    for (i = 0; i < all_num; i++) {
        if (pthreads_flag[i] == 'R') {
            if (pthread_create(&pthreads[i], NULL, read_file, (void*)(&pthread_index[i]))) {
                printf("readers %d pthread create error\n", i);
                exit(1);
            }
            printf("%d reader pthread is created\n", i+1);
        }
        else {
            if (pthread_create(&pthreads[i], NULL, write_file, (void*)(&pthread_index[i]))) {
                printf("writers %d pthread create error\n", i);
                exit(1);
            }
            printf("%d writer pthread is created\n", i+1);
        }
    }

    for (i = 0; i < all_num; i++) {
        if (pthreads_flag[i] == 'R') {
            if (pthread_join(pthreads[i], NULL)) {
                printf("readers %d pthread join error\n", i);
                exit(1);
            }
        }
        else {
            if (pthread_join(pthreads[i], NULL)) {
                printf("writers %d pthread join error\n", i);
                exit(1);
            }
        }
    }
    
    pthread_mutex_destroy(&mutex2);
    pthread_mutex_destroy(&mutex3);    
    return 0;
}
