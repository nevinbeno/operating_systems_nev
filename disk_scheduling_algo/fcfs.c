#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int fcfs(int*arr, int n, int head)
{
    int sum = 0;
    sum += abs(head - arr[0]);
    for (int i = 0; i < n - 1; i++)
        sum += abs(arr[i] - arr[i + 1]);
    return sum;
}

int main ()
{
    int n_req, start;
    printf("Enter the no. of requests: ");
    scanf("%d", &n_req);
    printf("Enter the initial head position: ");
    scanf("%d", &start);

    int arr[n_req];
    printf("Enter the request sequence: \n");
    for (int i = 0; i < n_req; i++)
        scanf("%d", &arr[i]);
    
    int ans = fcfs(arr, n_req, start);
    return 0;
}