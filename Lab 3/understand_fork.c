#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main ()
{
	if (fork() == 0)
	{
		if (fork() == 0)
			printf("Grandchild block: PID = %d\n. My parent's Pid: %d\n", getpid(), getppid());
		else
		{
			wait(NULL);
			printf("First child block: My PID: %d\n.My Parent (the root): %d\n", getpid(), getppid());
		}
	}
	else
	{
		wait(NULL);
		printf("I am the root. PID: %d\nDone\n", getpid());
	}
	return 0;
}