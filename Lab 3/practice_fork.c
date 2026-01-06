#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main ()
{
	int secret_num = 100;
	printf("Original: My PID is: %d\nsecret number is: %d\n", getpid(), secret_num);
	printf("=== FORKING NOW ===\n");
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("Fork Failed");
		return 1;
	}
	else if (pid == 0)
	{
		printf("This is from child process block.\nPID of child process = %d\nMy PPID is: %d\n", getpid(), getppid());
		secret_num = 500;
		printf("Child: Changing the value ion secret num to %d\n", secret_num);
	}
	else
	{
		sleep(1);
		printf("This is from parent block.\nMy PID = %d\nMy child is: %d\n", getpid(), pid);
		printf("Parent: My secret number is still %d; The child did not change mine. \n", secret_num);
	}
	return 0;
}