#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 100

int main ()
{
	char input_string[MAX] = {'\0'}; // initializing with null values;
	printf("Enter a string: ");
	fgets(input_string, MAX - 1, stdin); // getting the users tring using fgets()
	input_string[strcspn(input_string, "\n")] = '\0'; // removing new line character
	
	// printf("\nString length = %d\n", (int)strlen(input_string));	
	int in_fd[2];
	int out_fd[2];
	if (pipe(in_fd) == -1 || pipe(out_fd) == -1)
	{
		printf("Some error occurred with initializing the pipe. Returning 1\n");
		return 1;
	}
	int id = fork();
	if (id == -1)
	{
		printf("Some error occurred with fork(). Returning 2\n");
		return 2;
	}
	else if (id == 0)
	{
		close(out_fd[0]);
		close(in_fd[1]);
		
		char buffer[MAX] = {'\0'};
		read(in_fd[0], buffer, MAX);
		printf("\n == Child Process Update ==\nSuccessfully read from the pipe...\n");
		close(in_fd[0]);
		int length = (int)strlen(buffer);
		for (int i = 0; i < length / 2; i++)
		{
			char c = buffer[i];
			buffer[i] = buffer[length - i - 1];
			buffer[length - i - 1] = c;
		}
		write(out_fd[1], buffer, MAX);
		printf("\n == Child Process Update ==\nSuccessfully wrote into the pipe...\n");		
		close(out_fd[1]);
	}
	else
	{
		close(in_fd[0]);
		close(out_fd[1]);
		
		write(in_fd[1], input_string, MAX);
		close(in_fd[1]);
		
		wait(NULL); // wait till the child process finishes writing to the out_fd pipe. 
		
		char reverse[MAX] = {'\0'};
		read(out_fd[0], reverse, MAX);
		close(out_fd[0]);
		printf("\nThe reversed string is: %s\n", reverse);
		if (strcmp(reverse, input_string) == 0)
			printf("\n == Update from parent process ==\nReversed string and input string are the same, hence, palindrome\n");
		else
			printf("\nNot a palindrome. \n");
	}
	return 0;
}