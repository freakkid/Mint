#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

typedef int buffer_item;
#define BUFFER_SIZE 3
buffer_item buffer[BUFFER_SIZE]; // 循环队列缓冲区
int buffer_total_num = 0;     // 已满位的缓冲区数量
int buffer_index = 0;    // 消费的缓冲区位置下标

// 定义信号量
sem_t full, empty;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#define PTHREAD_SIZE 8
pthread_t pthreads[PTHREAD_SIZE];       // 所有线程数组
char pthreads_flag[PTHREAD_SIZE];       // 总的进程
int produce_num[PTHREAD_SIZE];          // 生产的产品号
int delay_times[PTHREAD_SIZE];      // 线程创建后申请资源的延迟时间
int op_times[PTHREAD_SIZE ];        // 进行生产或消费操作的时间
int pthread_index[PTHREAD_SIZE];    // 线程的下标，保证所有线程在运行时能正确获取自己的下标

int insert_item(buffer_item item) {
    if (buffer_total_num < BUFFER_SIZE) {
        buffer[(buffer_index+buffer_total_num)%BUFFER_SIZE] = item;
        ++buffer_total_num;
        return 0;
    }
    return -1;
}

int remove_item(buffer_item *item) {
    if (buffer_total_num > 0 && buffer[buffer_index] == *item) {
        buffer_index = (buffer_index + 1) % BUFFER_SIZE;
        --buffer_total_num;
        return 0;
    }
    if (buffer_total_num == 0) {
        printf("buffer_total_num = 0\n");
    }
    if (buffer[buffer_index] != *item) {
        printf("buffer[buffer_index] = %d, *item = %d\n", buffer[buffer_index], *item);
    }
    return -1;
}

void *producer(void *param) {
    int i = *((int*)(param));
    sleep(delay_times[i]);
    printf("%d producer is applying\n", i+1);

    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    printf("%d producer starts\n", i+1);
    sleep(op_times[i]);
    printf("%d producer ends\n", i+1);
    if (insert_item(produce_num[i])) {  
        printf("report pro error condition\n");
        exit(1);
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

void *consumer(void *param) {
    int i = *((int*)(param));
    sleep(delay_times[i]);
    printf("%d consumer is applying\n", i+1);
    
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    printf("%d consumer starts\n", i+1);
    sleep(op_times[i]);
    buffer_item removed_item = buffer[buffer_index];
    if (remove_item(&removed_item)) {
        printf("report con error condition\n");
        exit(1);
    }
    else
        printf("%d consumer ends\n", i+1);
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
}

// 对信号量等进行初始化
void init_sems() {
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);
    pthread_mutex_init(&mutex, NULL);
    int i = 0;
    for (i = 0; i < PTHREAD_SIZE; i++) {
        pthread_index[i] = i;
    }
}


int main(int argc, char *argv[]) {
    printf("produce&consumser\n");
    // 线程序号 线程角色(P/C) 存放或取出操作的开始时间 操作持续时间 生产产品号
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

    int p_num = 0;
    int c_num = 0;
    while (!feof(fin)) {
        int index, delay_time, op_time, produce_number;
        char flag;
        fscanf(fin, "%d %c %d %d", &index, &flag, &delay_time, &op_time);
        pthreads_flag[index-1] = flag;
        delay_times[index-1] = delay_time;
        op_times[index-1] = op_time;
        if (flag == 'P') {
            fscanf(fin, "%d\n", &produce_number);
            produce_num[index-1] = produce_number;
            ++p_num;
        }
        else {
            fscanf(fin, "\n");
            ++c_num;            
        }
    }
    fclose(fin);

    // 2.初始化函数
    init_sems();
    
    // 3.创建生成者进程/4.创建消费者进程
    int i, all_num = p_num + c_num;
    for (i = 0; i < all_num; i++) {
        if (pthreads_flag[i] == 'P') {
            if (pthread_create(&pthreads[i], NULL, producer, (void*)(&pthread_index[i]))) {
                printf("producers %d pthread create error\n", i);
                exit(1);
            }
            printf("%d producers pthread is created\n", i+1);
        }
        else {
            if (pthread_create(&pthreads[i], NULL, consumer, (void*)(&pthread_index[i]))) {
                printf("consumers %d pthread create error\n", i);
                exit(1);
            }
            printf("%d consumers pthread is created\n", i+1);
        }
    }

    for (i = 0; i < all_num; i++) {
        if (pthreads_flag[i] == 'P') {
            if (pthread_join(pthreads[i], NULL)) {
                printf("producers %d pthread join error\n", i);
                exit(1);
            }
        }
        else {
            if (pthread_join(pthreads[i], NULL)) {
                printf("consumers %d pthread join error\n", i);
                exit(1);
            }
        }
    }
    
    pthread_mutex_destroy(&mutex);
    return 0;
}