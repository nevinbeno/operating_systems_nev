#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int fifo(int f, int p, int* req)
{
    int faults = 0;
    int frames[f];
    int ptr = 0;
    
    for (int j = 0; j < f; j++)
        frames[j] = -1;

    for (int i = 0; i < p; i++)
    {
        bool found = false;
        for (int j = 0; j < f; j++)
            if (frames[j] == req[i])
            {
                found = true;
                break;
            }
        if (!found)
        {
            faults++;
            int replace = -1;
            for (int j = 0; j < f; j++)
                if (frames[j] == -1)
                {
                    replace = j;
                    break;
                }
            if (replace == -1)
            {
                replace = ptr;
                ptr  = (ptr + 1) % f;
            }
            frames[replace] = req[i];
        }
    }

    return faults;
}

int main ()
{
    int arr[] = {7, 0,1,2,0,3,0,4,2,3,0,3,2};
    printf("ans: %d\n", fifo(3, 13, arr));
    return 0;
}