#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int  main ()
{
	printf("Now, only one process exists. It is the parent. Its PID = %d\n", getpid());
	if (fork() == 0)
	{
		fflush(stdout);
		printf("Child process created, with PID = %d.\nThis will become 'ls'!\n", getpid());

		char *args[] = {"ls", "-l", NULL};
		execvp("ls", args); // new program loading intiated
		// if exec fails: the below line runs
		printf("Child process: exec failed. \n");
		exit(1);
	}
	else
	{
		wait(NULL);
		printf("Child process task completed by wait command\n");
		printf("Parent PID: %d\n", getpid());
	}
	printf("test\n");
	return 0;
}