#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
{
	pid_t pid = fork();
	if (pid == 0) // child process
	{
		printf("Hi ");
		fflush(stdout);
	}
	else if (pid > 0)
	{
		wait (NULL);
		printf("Nevin");
	}	
	else
	{
		perror("fork failed");
	}
	return 0;
}