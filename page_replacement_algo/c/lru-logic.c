#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 100

int lru_logic(int* request, int no_req, int frame)
{
    int frames[MAX_FRAMES];
    int recent[MAX_FRAMES];
    int faults = 0;

    for (int i = 0; i < frame; i++)
    {
        frames[i] = -1;
        recent[i] = -1;
    }
    
    for (int i = 0; i < no_req; i++)
    {
        int found = 0;
        int cur_page = request[i];

        for (int j = 0; j < frame; j++)
            if (cur_page == frames[j])
            {
                found = 1;
                recent[j] = i;
                break;
            }
        if (found == 0) // not found
        {
            int lru_index = 0;
            for (int j = 0; j < frame; j++)
            {
                if (frames[j] == -1)
                {
                    lru_index = j;
                    break;
                }
                if (recent[j] < recent[lru_index])
                    lru_index = j;
            }
            frames[lru_index] = cur_page;
            recent[lru_index] = i;
            faults++;
        }
    }
    return faults;
}