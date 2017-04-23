#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

/* 每次输入的命令规定不超过80个字符 */
#define MAX_LINE 80
#define HISTORY_NUM 11

int isGetHistoryList = 0;       // 判读是否按下Ctrl+C
char tmpInputBuffer[MAX_LINE];  // 存放输入命令的字符数组

typedef struct
{
    char data[HISTORY_NUM][MAX_LINE];
    int front;
    int rear;
} HistoryQueue;
HistoryQueue history_queue;     // 存放历史命令
// 初始化历史命令队列
int initHistoryQueue(HistoryQueue *Q) {
    Q->front = Q->rear = 0;
    return 1;
}
// 判断是否为空
int isEmptyQueue(HistoryQueue Q) {
    return Q.front == Q.rear;
}
// 判断是否队列已满
int isFullQueue(HistoryQueue Q) {
    return (Q.rear+1)%HISTORY_NUM == Q.front;
}
// 把命令存入队列
int enQueue(HistoryQueue *Q, char *command) {
    if (isFullQueue(*Q))
        Q->front = (Q->front + 1) % HISTORY_NUM;
    memset(Q->data[Q->rear], '\0', sizeof(Q->data[Q->rear]));
    strncpy(Q->data[Q->rear], command, strlen(command));
    Q->rear = (Q->rear + 1) % HISTORY_NUM;        
    return 1;
}

void getHistoryList() {
    isGetHistoryList  = 1;
    if (!isEmptyQueue(history_queue)) {
        putchar('\n');
        int index = history_queue.front;
        for (int i = 0; index != history_queue.rear; i++) {
            printf("[%d] - %s\n", i, history_queue.data[index]);
            index = (index + 1) % HISTORY_NUM;
        }
    }
    fflush(stdout);
}

char *getHistoryData(char *x) {
    if (!isEmptyQueue(history_queue)) {
        int index = (history_queue.rear - 1) % HISTORY_NUM;
        // 从后往前找匹配命令
        for (int i = 0; index != (history_queue.front-1)%HISTORY_NUM; i++) {
            if (strncmp(history_queue.data[index], x, strlen(x)) == 0) {
                return history_queue.data[index];
            }
            index = (index - 1) % HISTORY_NUM;
        }
    }
    return "";
}

char *getLastCommand() {
    if (isEmptyQueue(history_queue))
        return "";
    int index = (history_queue.rear - 1) % HISTORY_NUM;
    return history_queue.data[index];
}
// 对输入命令进行分解
void splitInputBuffer(char inputBuffer[], int length, char *args[], int *background) {
    memset(tmpInputBuffer, '\0', MAX_LINE);
    strncpy(tmpInputBuffer, inputBuffer, strlen(inputBuffer));

    int start = -1;  /* 命令的第一个字符位置 */
    int ct = 0;     /* 下一个参数存入args[]的位置 */
    // 检查inputbuffer每一个字符
    for (int i = 0; i < length; i++) {
        switch(inputBuffer[i]) {
            case ' ':
            case '\t':          /* 字符为分割参数的空格或制表符(tab)'\t'*/
                if (start != -1) {
                    args[ct] = &inputBuffer[start];
                    ct++;
                }
                inputBuffer[i] = '\0';
                start = -1;
                break;
            case '\n':          /* 命令行结束 */
                if (start != -1) {
                    args[ct] = &inputBuffer[start];
                    ct++;
                }
                inputBuffer[i] = '\0';
                args[ct] = NULL;
                break;
            default:
                if (start == -1)
                    start = i;
                if (inputBuffer[i] == '&') {
                    *background = 1;
                    inputBuffer[i] = '\0';
                }
        }
    }
    args[ct] = NULL; /* 命令字符数 > 80 */
    // 如果用户按下回车('\n')，则将args第一个元素设为空字符，避免段错误
    if (args[0] == NULL) {
        args[0] = "";
        args[1] = NULL;
    }
}

void setup(char inputBuffer[], char *args[], int *background) {
    int length; /* 命令的字符数目 */
    
    memset(inputBuffer, '\0', MAX_LINE);
    /* 读入命令行字符，存入inputBuffer */
    length = read(STDIN_FILENO, inputBuffer, MAX_LINE);

    if (length == 0)    /* 输入ctrl+d，结束shell程序 */
        exit(0);
    if (length < 0) {
        perror("error reading the command");
        exit(-1);
    }
    
    splitInputBuffer(inputBuffer, length, args, background);
}


int main() {
    initHistoryQueue(&history_queue);    // 初始化历史命令记录队列

    char inputBuffer[MAX_LINE]; /* 这个缓存用来存放输入的命令*/
    int background;             /* ==1时，表示在后台运行命令，即在命令后加上'&' */
    char *args[MAX_LINE/2+1];   /* 命令最多40个参数 */
    pid_t pid;

    while(1) {
        background = 0;
        isGetHistoryList = 0;    

        printf(" COMMAND->");
        fflush(stdout); // 输出缓冲区内容
        
        signal(SIGINT, getHistoryList);

        if (isGetHistoryList != 0) {
            continue;    
        }
        // 接收用户命令并分解
        setup(inputBuffer, args, &background);  
        // 判断命令是不是 "r" 开头的
        if (strcmp(args[0], "r") == 0) {
            // 对inputBuffer清零
            memset(inputBuffer, '\0', strlen(inputBuffer));
            // 输入 "r x" 格式时，
            if (args[1] != NULL) {
                // 寻找可以匹配的最近的命令
                char *oldCommand = getHistoryData(args[1]);
                strncpy(inputBuffer, oldCommand, strlen(oldCommand));
            }
            else { // 输入 "r" 时，
                // 获取最后一条命令
                char *oldCommand = getLastCommand();
                puts(oldCommand);
                strncpy(inputBuffer, oldCommand, strlen(oldCommand));
            }
            if (inputBuffer == NULL)
                continue;
            else {
                // 分解 inputBuffer
                splitInputBuffer(inputBuffer, strlen(inputBuffer), args, &background);
            }
        }
        // 把命令放进历史信息队列
        enQueue(&history_queue, tmpInputBuffer);
        // 产生子进程
        pid = fork();
        if (pid < 0) {
            printf("fork error\n");
            exit(1);
        } 
        else if (pid == 0) {
            execvp(args[0], args);
            exit(0);
        }
        else {
            if (background == 0)
                wait(0);
        }

    }

}