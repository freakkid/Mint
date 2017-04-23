#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void waiting();
void stop();
int wait_mark;

int main() {
	int p1, p2;
	while ((p1 = fork()) == -1);

	if (p1 > 0) {
		while ((p2 = fork()) == -1);

		if (p2 > 0) {
			wait_mark = 1;
			signal(SIGSTOP, SIG_IGN);
			signal(SIGINT, stop);
			waiting();
			kill(p1, 16);
			kill(p2, 17);
			wait(0);
			wait(0);
			printf("parent process is killed!\n");
			exit(0);
		} else {
			wait_mark = 1;
			signal(SIGSTOP, SIG_IGN);
			signal(SIGINT, SIG_IGN);
			signal(17, stop);
			waiting();
			printf("child process 2 is killed by parent!\n");
			exit(0);
		}
	} else {
		wait_mark = 1;
		signal(SIGSTOP, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		signal(16, stop);
		waiting();
		printf("child process 1 is killed by parent!\n");
		exit(0);
	}
}

void waiting() {
	while(wait_mark != 0);
}

void stop() {
	wait_mark = 0;
}