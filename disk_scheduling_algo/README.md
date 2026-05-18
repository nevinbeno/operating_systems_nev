# Disk Scheduling Algorithms
![Disk Scheduling](https://img.shields.io/badge/Concept-Disk_Scheduling-yellow)
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
## 4. C-SCAN
```c
    int c_scan(int* arr, int n, int head)
    {
        if (n == 1)
            return abs(head - arr[0]);
        qsort(arr, n, sizeof(int), compare);
        if (head >= arr[n - 1])
            return head;
        else if (head < arr[0])
            return head + arr[n - 1] + abs(arr[n - 1] - arr[0]);
        else
        {
            int index = binarySearch(arr, n, head);
            index++;
            return head + arr[n - 1] + abs(arr[n - 1] - arr[index]);
        }
    }
```
## 5. C-LOOK
```c
    int c_look(int* arr, int n, int head)
    {
        if (n == 1)
            return abs(head - arr[0]);
        qsort(arr, n, sizeof(int), compare);
        if (head >= arr[n - 1])
            return head - arr[0];
        else if (head < arr[0]) // jump
            return abs(arr[n - 1] - head) + abs(arr[n - 1] - arr[0]);
        else
        {
            int index = binarySearch(arr, n, head);
            index++;
            return (head - arr[0]) + (arr[n - 1] - arr[0]) + abs(arr[n - 1] - arr[index]);
        }
    }
```