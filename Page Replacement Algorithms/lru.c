#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node* lptr;
    struct node* rptr;
};

struct hashEntry
{
    int page;
    struct node* address;
    struct hashEntry* next;
};

struct node* create_node(int x)
{
    struct node* p = malloc(sizeof(struct node));
    p->lptr = NULL;
    p->rptr = NULL;
    p->value = x;
    return p;
}

void lru_algorithm(int no_of_pages, int* req, int no_of_frames, int* frame_arr)
{
    struct node* head = NULL;
    for (int i = 0; i < no_of_pages; i++)
    {
        if (head == NULL)
        {
            struct node* new = create_node(req[i]);
            head = new;
        }
        else
        {

        }
    }
}

int main ()
{
    int no_of_pages;
    printf("Enter the no. of pages: ");
    scanf("%d", &no_of_pages);
    int page_request[no_of_pages];
    printf("Enter those pages: \n");
    for (int i = 0; i < no_of_pages; i++)
    {
        printf("Page %d: ", i + 1);
        scanf("%d", &page_request[i]);
    }

    int no_of_frames;
    scanf("Enter the no. of frames: ");
    scanf("%d", &no_of_frames);
    int frame_arr[no_of_frames];
    for (int i = 0; i < no_of_frames; i++)
        frame_arr[i] = -1;
    
    printf("The final structure of the frames: \n");
    for (int i = 0; i < no_of_frames; i++)
        
    return 0;
}