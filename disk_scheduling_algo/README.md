# Disk Scheduling Algos: 
## 1. FCFS
```c
    int sum = 0;
    sum += abs(head, arr[0]);
    for (int i = 0; i < n - 1; i++)
        sum += abs(arr[i] - arr[i + 1]);
    return sum;
```
## 2. SCAN (Elevator algorithm)
> Assumes first, we go towards the left direction
```c
    int scan(int head, int n_req, int* arr)
    {
        qsort(arr, n_req, sizeof(int), compare);
        if (head >= arr[n_req - 1])
            return head;
        else
            return head + arr[n_req - 1];
    }
```
## 3. LOOK
```c
    int look(int* arr, int size, int head)
    {
        qsort(arr, size, sizeof(int), compare);
        int sum = 0;
        sum += abs(arr[0] - arr[size -1]);
        if (head > arr[size - 1])
            sum += abs(head - arr[size - 1]);
        else
            sum += abs(head - arr[0]);
        return sum;
    }
```