# `strace`: System-call trace
This command shows, the system calls made by a program during execution. The command is: <br>
```bash
    $ strace <executable> # any executable file
```
- We need the executable file, so we compile using

    ```bash
    $ gcc fileio.c -o fileio
    ```
For running, we have 2 options: 
- Direct running in terminal: This prints all the system call and related outputs of strace in the terminal which can make the terminal lool messy. 

    ```bash
    $ strace ./fileio    
    ```
- Store it into a separate file, and then we could look inside that file or use the `cat` command to see the output in the terminal. 
    ```bash
    $ strace -o myOutput.txt ./fileio
    ```
_____
## Outputs explained (only needed things are included): 
1. `fopen()` <=> `openat()`:<br>
```txt
openat(AT_FDCWD, "test.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
```
### Meaning: 
- `openat()`: system call
- `AT_FDCWD`: use the present working directory. (openat() also provides provision to open things in any other locations, when given the specific path)
- `"test.txt"`: file name.
- `O_WRONLY`: write only.
- `O_CREATE`: create if not exists. 
- `O_TRUNC`: "if the file already exists, then, erase its content".
- `0666`: Octal repressentation, of file permissions, Owner User Others; 6 = 4 + 2, means, read write permissions. (0666 => rw-rw-rw)
- `3`: file descriptor returned. 

## Deep dive: 

### `file descriptor`: 
A file descriptor is an integer used by the OS to uniquely identify an open file or I/O resource in a process. Generally, <br>
- `0`: stdin
- `1`: stdout
- `2`: stderr

Now, when a new thing is allocated, it is most likely to get the file descriptor as `3`. OS uses this as a identification mark of this filem amd is also used to point to this file, when it needs to access the file in any way (close, write, read etc)