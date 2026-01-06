#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	pid = fork();
	if (pid < 0)
	{
		perror("ERROR: fork() failed. \n");
		return 1;
	}
	else if (pid == 0)
	{
		printf("Child process created successfully. \n");
		printf("PID of child process = %d\n", getpid());
		printf("PPID: %d\n", getppid());
		sleep(30);
	}
	else
	{
		printf("Parent: PID = %d\n", getpid());
		printf("PPID: %d\n", getppid());
		sleep(30);
	}
	printf("Done\n");
	return 0;
}