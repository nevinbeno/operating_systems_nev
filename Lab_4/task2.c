#include <stdio.h>
#include <stdlib.h> // EXIT_FAILURE
#include <sys/wait.h> // wait()
#include <sys/types.h>  // fork(), read(). write(), close(), ....
#include <unistd.h> // pid_t
#include <string.h>

#define MAX_SIZE 100

int main ()
{
    char string[MAX_SIZE] = {'\0'};
    printf("Enter a string: ");
    fgets(string, MAX_SIZE - 1, stdin);
    string[strcspn(string, "\n")] = '\0';

    int p1[2], p2[2];
    if (pipe(p1) == -1 || pipe(p2) == -1)
    {
        perror("pipe()");
        exit(EXIT_FAILURE);
    }

    int str_len = strlen(string);
    pid_t cpid = fork();
    if (cpid == -1)
    {
        perror("fork()");
        exit(EXIT_FAILURE);
    }
    else if (cpid == 0)
    {
        close(p1[1]); // close the write end of p1. 
        close(p2[0]); // close the read end of p2
        char buffer[str_len + 1];
        read(p1[0], buffer, str_len);
        buffer[str_len] = '\0'; // null termination
        for (int i = 0; i < str_len / 2; i++)
        {
            char ch = buffer[i];
            buffer[i] = buffer[str_len - i - 1];
            buffer[str_len - i - 1] = ch;
        }
        write(p2[1], buffer, str_len);
        close(p2[1]);
        close(p1[0]);
    }
    else
    {
        close(p1[0]);
        close(p2[1]);

        write(p1[1], string, str_len);
        close(p1[1]);

        char rev[str_len + 1];
        read(p2[0], rev, str_len);
        rev[str_len] = '\0';
        close(p2[0]);

        wait(NULL);
        
        if (strcmp(rev, string) == 0)
            printf("palindrome\n");
        else
            printf("not palindrome\n");
    }
    return 0;
}