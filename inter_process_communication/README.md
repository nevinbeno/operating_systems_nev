# IPC
## Summary: 
```txt
    child process
    {
        receive the data
        read(fd index, address of the content, size in Bytes of the content received);
        do computation

        write in the similar way

        close those pipe ends when not needed
    }

    parent process
    {
        send the data
        wait till child returns the data
        receive data
        display
    }
```