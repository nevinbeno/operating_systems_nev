// calculate b^2 - 4*a*c using pipe. 
// child process calculates b^2, and gives to parent
// parent calculates 4*a*c, and and then evaluates the root. 

#include <stdio.h>
#include <math.h> // for sqrt funcN
#include <unistd.h> // for fork(), read(). write() etc
#include <sys/types.h> // for pid_t
#include <sys/wait.h>
#include <stdlib.h>

int main ()
{
	int a = 4, b = 5, c = 1; // 25 - 4(4) = 25 - 16 = 9 => sqrt(9) = 3.0
	int my_pipe[2];
	if (pipe(my_pipe) == -1)
	{
		perror("pipe()");
		exit(EXIT_FAILURE);
	}
	printf("pipe(my_pipe) = %d\n", pipe(my_pipe));
	pid_t cpid = fork();
	if (cpid  == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	else if (cpid == 0)
	{
		// child process activates
		close(my_pipe[0]); // we close the read end
		int value = b*b;
		write(my_pipe[1], &value, sizeof(int));
		close(my_pipe[1]);
	}
	else
	{
		// parent process; we need to read the value in pipe
		wait(NULL);
		close(my_pipe[1]); // close the write end
		int readme;
		read(my_pipe[0], &readme, sizeof(int));
		int t2 = 4*a*c;
		int inside = readme - t2;
		double answer = sqrt(inside);
		printf("The answer is: %lf\n", answer);
	}
	return 0;
}
