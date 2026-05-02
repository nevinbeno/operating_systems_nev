# Page Replacement Algorithms

## LRU (Least Recently Used)
- The content of the frame which was least recently updated is selected to replace. 
### Algorithm (Doubly Linked List & Hash Table):
- Start
- Get the variables like
    ```txt
    no_of_pages
    the page request array
    no of frames
    ```
- Initialize a doubly linked list, 
    ```txt
    Each node content is intented to be page number. 
    No. of nodes should never exceed no_of_frames.  
    ```
- Create a hash table:
    ```cpp
    #include <unorderd_map>
    unordered_map<int, list<int>::iterator> hash_table;
    ```

    ```txt
    hash_table: <page_number, associated node address>
    ```
- For each of those pages: 
    ```txt
    if the page entry is in hash table
        pick that node.
        shift that node to the beginning position of the Doubly Linked List. 
        update the hash table entry for that key (new address may be allotted).
    else
        if (no of nodes >= no_of_frames)
            delete the content of the least recently used frame.
            delete the corresponding entry from the hash table. 
        add the new hash table entry for the new page. 
        insert a new node for the page at the beginning. 
    ```
- Now, the final configuration of DLL will give you the pages in the frames!
- Stop.
_______
## FIFO (First In First Out)