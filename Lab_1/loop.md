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

### OS Commands in action
```bash
$ gedit loop.c & # gedit is itself started as a background process
```
- gedit is itself started as a backgroud process. 
- We do not have to close the gedit window for any further termianl executions. 
- But we must save the gedit window to make the changes in effect. 
2.
command:
```bash
$ ./loop > new.txt & # command
```
output: 
```
[1] 7291
```
- `[1]`: job number. 
- `7291`: Process ID (PID).
- This command creates a job, with that process ID. 
> NB: Whenever you start a background process, you will get the Job number and PID of it. 
3. 
```bash
$ jobs # to show the current jobs
```
output: 
```
[1]-  Running                 gedit loop.c &
[2]+  Running                 ./loop > loop.txt &
```
- `+`: denote the default job. Any commans like `fg` will treat as if `fg %2`
- `-`: denote the job, which was default previously. 
- `Running`: still being executed. 
- `Done`: finished. 
4. 
```bash
$ jobs -l # also gives the PID, which is not given by the jobs
```
5. 
command: 
```bash
$ ps -o pid,ppid,stat,cmd
```
output: 
```
    PID    PPID STAT CMD
   4700    4692 Ss   bash
   7291    4700 S    ./loop
   7380    4700 R+   ps -o pid,ppid,stat,cmd
```
- PID: Process ID.
- PPID: Parent PID.
- STAT: Process State.
    - `S`: Sleeping (waiting for some event ot timer)
    - `s`: session leader
    - `R`: Running (currently using CPU)
    - `+`: Process is in the foreground of its controlling terminal. 
- CMD: The command that started the process. 
6. 
command: 
```bash
$ ps -o pid,ppid,stat,cmd -p 4700 # $ ps -o pid,ppid,stat,cmd -p <PID>
```

## Theory: 
> What happens when you open a terminal?<br>
> - You click Terminal<br>
> - OS starts a terminal emulator process (e.g. gnome-terminal)<br>
> - That terminal emulator creates another process: the shell (bash, zsh, etc.)<br>

- **terminal emulator** is a process, and it runs a shell(bash), which become the parent of its commands. Shell (bash) is a process created by the terminal emulator. 
- Since each shell is also a process, 
    - it has got a PID. 
    - This shell acts as the **parent process** of all the commands that are initiated and executed INSIDE it. That is the reason, why the PPID of all the other commands initiated inside this shell has got the same PPID, which is the PID of the current shell. 
- This is the reason why Bash is assigned with the STAT `Ss`, which is a mix of two states - `s` (session lead) and `S` (sleeping). 
- Every command or process you run is considered as the **child process** of this shell. 
______
## Background and Foreground Processes
- When a foreground process is initiated in a terminal, no other actions could be performed in that terminal  unless the process has terminated. 
### Background Process to Foregroud Process
```bash
$ fg %1 # $ fg %<jobID>
```
### Foreground Process to Background Process
1. Step 1: Suspend the foreground job
```
Ctrl + Z 
```
2. Step 2: Resume it in background
```bash
$ bg %1 # $ bg %<jobID>
```
## Code: 
[View the code](loop.c)