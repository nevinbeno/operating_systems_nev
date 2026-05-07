#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_CAPACITY 50

int no_of_nodes = 0;

struct node
{
    int value;
    struct node* lptr;
    struct node* rptr;
};

struct node* tail = NULL;

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
        exit(0);
    }
    ht->capacity = cap;
    ht->current_size = 0;
    ht->buckets = (struct hash_entry**)calloc(cap, sizeof(struct hash_entry*));
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
        exit(0);
    }
    new->page_no = key;
    new->node_address = addr;
    new->next = ht->buckets[id];
    ht->buckets[id] = new;
    ht->current_size++;

    return;
}

void delete_hash_entry(struct hash_table* ht, int key)
{
    unsigned int id = hash_function(key, ht->capacity);
    struct hash_entry* head = NULL;
    struct hash_entry* prev = NULL;
    head = ht->buckets[id];
    while(head)
    {
        if (head->page_no == key)
        {
            if (prev)
                prev->next = head->next;
            else
                ht->buckets[id] = head->next;
            free(head);
            ht->current_size--;
            return;
        }
        else
        {
            prev = head;
            head = head->next;
        }    
    }
}

struct node* create_node(int x)
{
    struct node* p = NULL;
    p = malloc(sizeof(struct node));
    if (p == NULL)
    {
        printf("Error: Node creation failed, Program exiting\n");
        exit(0);
    }
    p->lptr = NULL;
    p->rptr = NULL;
    p->value = x;
    return p;
}

struct node* insert_node(struct node* head, int key)
{
    struct node* new = NULL;
    new = create_node(key);
    if (head == NULL)
    {
        head = new;
        tail = head;
    }
    else
    {
        head->lptr = new;
        new->rptr = head;
        head = new;
    }
    no_of_nodes++;
    return head;
}

struct node* delete_node(struct node* head)
{
    if (head && head->rptr == NULL) // single node case
    {
        free (head);
        head = NULL;
        tail = NULL;
        no_of_nodes = 0;
    }
    else
    {
        struct node* rmv = tail;
        tail = tail->lptr;
        if (tail)
            tail->rptr = NULL;
        free(rmv);
        no_of_nodes--;
    }
    return head;
}

void lru_algorithm(int no_of_pages, int* req, int no_of_frames)
{
    struct node* head = NULL;
    struct hash_table* ht = NULL;
    ht = create_table(HASH_TABLE_CAPACITY);
    for (int i = 0; i < no_of_pages; i++)
    {
        if (head == NULL)
        {
            head = insert_node(head, req[i]);
            insert_update(ht, head->value, head);
        }
        else
        {
            // the DLL is not empty. 
            struct node* check = NULL;
            check = search(ht, req[i]);
            if (check) // the page entry is found... then just reordering is enough
            {
                if (check != head)
                {
                    struct node* left = NULL;
                    struct node* right = NULL;
                    right = check->rptr;
                    left = check->lptr;
                    if (left)
                    {
                        if (tail == check)
                            tail = left;
                        left->rptr = right;
                        if (right)
                            right->lptr = left;
                    }
                    check->lptr = NULL;
                    check->rptr = head;
                    head->lptr = check;
                    head = check;
                }    
            }
            else
            {
                if (no_of_nodes >= no_of_frames)
                {
                    // delete the least recently used node
                    delete_hash_entry(ht, tail->value);
                    head = delete_node(head);
                }
                // insert a new node the left of head node in DLL. 
                head = insert_node(head, req[i]);
                // make a hash table entry
                insert_update(ht, req[i], head);
            }
        }
    }

    printf("\nThe final structure of the Frames: \n");
    struct node* temp = head;
    while(temp)
    {
        printf("%d, ", temp->value);
        temp = temp->rptr;
    }
    printf("\nDONE!\n");
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
    printf("Enter the no. of frames: ");
    scanf("%d", &no_of_frames);  
    lru_algorithm(no_of_pages, page_request, no_of_frames);
    return 0;
}