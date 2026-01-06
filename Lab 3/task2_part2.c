// this is the terminal_simul
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main ()
{
	pid_t pid = fork();
	if (pid == 0)
	{
		printf("Child process: Executing myadde using the exec mthd\n");
		fflush(stdout);
		char *args[] = {"./myadder", "10", "20", NULL};
		execvp(args[0], args);
		// these parts are not to be executed if the exec run
		perror("execvp failed\n");
		exit(1);
	}
	else if (pid > 0)
	{
		wait(NULL);
		printf("Parent window: Child process done\n");
	}
	else
	{
		perror("fork failed\n");
	}
	return 0;
}