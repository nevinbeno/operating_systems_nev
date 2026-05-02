#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node* lptr;
    struct node* rptr;
};

struct hash_entry
{
    int page_no; // key
    struct node* node_address; // value
    struct hash_entry* next;
};

struct hash_table
{
    int capacity;
    int current_size;
    struct hash_entry** buckets;
};

unsigned int hash_function(int key, int capacity)
{
    key ^= (key >> 16);
    key *= 0x7feb352d;
    key ^= (key >> 15);
    key *= 0x846ca68b;
    key ^= (key >> 16);
    return key % capacity;
}

struct hash_table* create_table(int cap)
{
    struct hash_table* ht = NULL;
    ht = (struct hash_table*)malloc(sizeof(struct hash_table));
    if (ht == NULL)
    {
        printf("Error in creating hash table; Exiting\n");
        return EXIT_FAILURE;
    }
    ht->capacity = cap;
    ht->current_size = 0;
    ht->buckets = (struct hash_entry**)calloc(cap, sizeof(struct node*));
    return ht;
}

struct node* search(struct hash_table* ht, int key)
{
    unsigned int index = hash_function(key, ht->capacity);
    struct hash_entry* head = ht->buckets[index];
    while (head)
    {
        if (head->page_no == key)
            return head->node_address;
        else
            head = head->next;
    }
    return NULL;
}

void insert_update(struct hash_table* ht, int key, struct node* addr)
{
    struct hash_entry* head = NULL;
    unsigned int id = hash_function(key, ht->capacity);
    head = ht->buckets[id];
    while(head) // if found => update
    {
        if (head->page_no == key)
        {
            head->node_address = addr;
            return;
        }
        else
            head = head->next;
    }
    // if not found, then, fresh insert
    struct hash_entry* new = NULL;
    new = (struct hash_entry*)malloc(sizeof(struct hash_entry));
    if (new == NULL)
    {
        printf("Error: hash table entry creation failed. Exiting...\n");
        return EXIT_FAILURE;
    }
    new->page_no = key;
    new->node_address = addr;
    new->next = ht->buckets[id];
    ht->buckets[id] = new;
    ht->current_size++;

    return;
}

struct node* create_node(int x)
{
    struct node* p = malloc(sizeof(struct node));
    p->lptr = NULL;
    p->rptr = NULL;
    p->value = x;
    if (p == NULL)
    {
        printf("Error: Node creation failed, Program exiting\n");
        return EXIT_FAILURE;
    }
    else
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