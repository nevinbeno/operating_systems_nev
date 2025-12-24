# 1. `ps`: Process Status
## Code explanation:
### 1. Need of `fflush(stdout);`
In C language, `printf()` is line bufered for terminal and, **fully buffered** for files. Meaning, writing to files happen only if: 
- The buffer gets filled. 
- (or) The program is terminated. 

Hence, usage of this `fflush(stdout)` will force the program to write stdouts to the file immedeately. 
```c
fflush(stdout);
```
### 2. Infinitly running program
The program contain
```c
while (1)
{

}
```
which never terminates => infinitly running program. 
**For such programs, the process ID will be the same one created at the time of the commencement of its execution.**
## Compiling & Execution
```bash
$ gcc loop.c -o loop # name of the executable == loop
$ ./loop > output.txt & # execution command
```
- `./loop > output.txt`: if any output (stdout based) is generated from the executable, **REDIRECT IT** to some text file named `output`. **DO NOT PRINT ANYTHING TO THE TERMINAL SCREEN**. (So, the terminal remain clean.)
- `&`: the execution is to be done as a background process.
[View the code](loop.c)
### Outputs explained: 
```bash
benoJR:~/Documents/OS_Lab/Lab_1$ ./loop > new.txt & # command
[1] 7291 # result
```
- `[1]`: job number. 
- `7291`: Process ID (PID).
- This command creates a job, with that process ID. 
