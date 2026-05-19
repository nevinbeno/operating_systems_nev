#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

void pipe_error()
{
    printf("Error occurred when initializing pipes. \n");
    exit(0);
}

void fork_error()
{
    printf("Error occurred when forking. \n");
    exit(0);
}

int main ()
{
    int fd1[2], fd2[2];
    
    if (pipe(fd1) == -1 || pipe(fd2) == -1)
        pipe_error();
    int id = fork();

    if (id < 0)
        fork_error();

    if (id == 0)
    {
        close(fd1[1]);
        close(fd2[0]);

        int val;
        read(fd1[0], &val, sizeof(int));
        close(fd1[0]);

        val += 10;
        write(fd2[1], &val, sizeof(int));
        close(fd2[1]);
    }
    else
    {
        int n;
        printf("Enter the 'n' value: ");
        scanf("%d", &n);

        close(fd1[0]);
        close(fd2[1]);

        write(fd1[1], &n, sizeof(int));
        close(fd1[1]);

        wait(NULL);

        int result;
        read(fd2[0], &result, sizeof(int));
        close(fd2[0]);

        printf("The result from chld process: %d\n", result);
    }

    return 0;
}