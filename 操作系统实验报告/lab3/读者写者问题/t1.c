#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 20
pthread_t pthreads[THREAD_NUM];
char pthreads_flag[THREAD_NUM];
int delay_times[THREAD_NUM];
int op_times[THREAD_NUM];
int pthread_index[THREAD_NUM];    // 线程的下标，保证所有线程在运行时能正确获取自己的下标

int reader_count = 0;   // 当前读者数目
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 互斥对象控制对read_count修改
sem_t fmutex;            // 写写互斥和读写互斥的临界对象
sem_t wmutex;           // 阻塞write进程


void *read_file(void *param) {
    int i = *((int*)(param));
    sleep(delay_times[i]);        
    printf("%d reader is applying\n", i+1);

    pthread_mutex_lock(&mutex); // 保证对全局read_count修改是互斥的
    if (reader_count == 0) {    // 等待写者写完释放fmutex
        sem_wait(&fmutex);
    }
    ++reader_count;
    pthread_mutex_unlock(&mutex);

    // read
    printf("%d reader starts reading\n", i+1);
    sleep(op_times[i]);
    printf("%d reader ends reading\n", i+1);

    pthread_mutex_lock(&mutex);
    --reader_count;
    if (reader_count == 0) {    // 所有读者读完了，写者可以写了
        sem_post(&fmutex);
    }
    pthread_mutex_unlock(&mutex);
    return (NULL);
}

void *write_file(void *param) {
    int i = *((int*)(param));
    sleep(delay_times[i]);        
    printf("%d writer is applying\n", i+1);
    // 把许多写线程阻塞在这里，保证读操作会比写操作优先获得释放的fmutex
    sem_wait(&wmutex);      
    // 保证每次阻塞在fmutex的写进程只有一个，只有一个写进程等待fmutex的释放
    sem_wait(&fmutex);
    // write
    sleep(op_times[i]);
    printf("%d writer ends writing\n", i+1);

    sem_post(&fmutex);
    sem_post(&wmutex);
    return (NULL);
}

void init_sems() {
    pthread_mutex_init(&mutex, NULL);
    sem_init(&fmutex, 0, 1);
    sem_init(&wmutex, 0, 1);
    int i = 0;
    for (i = 0; i < THREAD_NUM; i++) {
        pthread_index[i] = i;
    }
}

int main(int argc, char *argv[]) {
    printf("reader first\n");
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
    
    // 初始化信号量
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
    
    pthread_mutex_destroy(&mutex);
    return 0;
}
