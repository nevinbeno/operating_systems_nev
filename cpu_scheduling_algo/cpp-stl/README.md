# CPU Scheduling (using C++ STL)

## SRTF Algorithm
```txt
1. Start.
2. Sort the array of struct based of arrival time.
3. Shifting of time axis to the p[0].at
4. Repeat till all processes are completed.
    4.1. Find all process that have arived by the time.
    4.2. Add those processes into the queue. 
    4.3. If queue is empty (CPU idle), increment time.
    4.4. Else:
        4.4.1. Sort the queue based on remaining time. (For tie breaking, use Pid)
        4.4.2. Access the front element from the queue. 
        4.4.3. Decrement 1 unit of remaining time. 
        4.4.4. Increment time. 
        4.4.5. Calculate ct, rt, etc... if suitable.
        4.4.6. Increment "completed" if suitable. 
5. Display the specs
6. Stop. 
```

## LRTF Algorithm
```txt
    Just change the sign in the Remaining time comparator. 
```