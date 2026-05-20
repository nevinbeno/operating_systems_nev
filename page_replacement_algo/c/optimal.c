#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int optimal(int f, int p, int* req)
{
    int faults = 0;
    int frames[f];
    for (int i = 0; i < f; i++)
        frames[i] = -1;
    
    for (int i = 0; i < p; i++)
    {
        bool found = false;
        for (int j = 0; j < f; j++)
            if (req[i] == frames[j])
            {
                found = true;
                break;
            }
        if (!found)
        {
            int free_index = -1;
            for (int j = 0; j < f; j++)
                if (frames[j] == -1)
                {
                    free_index = j;
                    break;
                }
            if (free_index == -1) // there is no free slots, so, should apply optimal policy
            {
                int far = -1;
                for (int j = 0; j < f; j++)
                {
                    int next_use = 99999;
                    for (int k = i + 1; k < p; k++)
                    {
                        if (frames[j] == req[k])
                        {
                            next_use = k;
                            break;
                        }
                    }
                    if (next_use > far)
                    {
                        far = next_use;
                        free_index = j;
                    }
                }
            }
            faults++;
            frames[free_index] = req[i];
        }
    }
    return faults;
}

int main()
{

    return 0;
}