# `/proc/loadavg`
    ```bash
    ~$ cat /proc/loadavg
    ```
Output: 
```
0.21 0.28 0.22 2/1243 7607
```
### Interpretation: 
- The first three values denote the CPU load for the last 1 min, 5 min, 15 min respectively. 
- All values << 1 => CPU is lightly loaded. 
- `2/1243`: no. of process currently (runnable | running | ready) / total no of processes in the system that has a PID right now. 
#### So what is 1243?
1243 = total number of processes currently existing in the system. <br>
This includes:
- Running
- Sleeping
- Waiting for I/O
- Daemons
- Background services
- Kernel threads

Basically: everything that has a PID right now.
______
#### What is that `7606`:
- Any process ID, like, of this ``cat command, etc...