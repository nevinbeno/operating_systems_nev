# OS lab 2
### System scan (`system_scan.sh`)
- This shell program automates the scan of a system.
- Run: 
    ```bash
    ~$ bash system_scan.sh
    ```
- [Click here](system_scan.sh) to see the code
### Time program (`time_program.c`)
- The motivation for creating this C file was NOT to run it just like any othe C files, but, to know the context switches made for a *specific* program (`ctxt`). 
- So, we made this program, compile it, and run the executable using another shell program (another shell program is preferred to automate the scans. Else, we'd have to do all those commands in the terminal, which can create the cases of timeouts.) 
- Compiling the C code: 
    ```bash
    ~$ gcc time_program -o time_program
    ```
- Run the `proc_pid_ctxt.sh`: 
    ```bash
    ~$ bash proc_pid_ctxt.sh
    ```
    > The C program execution command is contained inside the shell code (`./time_program &`). When the shell code run, the C program also is made to run in the background, and the voluntary and non-voluntary context switches are measured. Any output will be redirected to a text file so that the terminal is free from any stdouts.
- [time_program.c](time_program.c)
- [proc_pid_ctxt.sh](proc_pid_ctxt.sh)
### `key_press.c`
- The [previous code](#time-program-time_programc) was too short for the processor to make any visible context switches, so ,this program was made, with an intention to bring some non-zero context switches. 
- This program uses 'getchar()', which waits for input from user. So, if we could lag the input given, then, we may potentially find some context switches. 
- Compile: 
    ```bash
    ~$ gcc key_press.c -o key_press
    ```
- Run the bash
    ```bash
    ~$ bash shell_code_keyPress.sh
    ```
