#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
using namespace std;

void lru_algorithm(int pages, vector<int>& req, int frames)
{
    int no_misses;
    list<int> dll;
    unordered_map<int, list<int>::iterator> hash_table;
    for (int i = 0; i < pages; i++)
    {
        int key = req[i];
        auto it = hash_table.find(key);
        if (it != hash_table.end()) // there is a match in the hash table
        {
            dll.splice(dll.begin(), dll, it->second);
            it->second = dll.begin();
        }
        else // not in hash table
        {
            no_misses++;
            if (dll.size() >= frames)
            {
                int value_of_popped = dll.back();
                hash_table.erase(value_of_popped);
                dll.pop_back();
            }
                dll.push_front(key);
                hash_table[key] = dll.begin();
        }
    }
    cout<<"The total no. of pages: "<<pages<<endl;
    cout<<"Total no of page misses: "<<no_misses<<endl;
    cout<<"Total no of page hits: "<<pages - no_misses<<endl;
    cout<<"The final configuration of the frames: "<<endl;
    for (int element : dll)
        cout<<element<<" ";
    cout<<endl;
}

int main ()
{
    int no_of_pages;
    cout<<"Enter the number of pages: ";
    cin>>no_of_pages;
    
    vector<int> request(no_of_pages);
    cout<<"Enter the pages: "<<endl;
    for (int i = 0; i < no_of_pages; i++)
    {
        cout<<"Page "<<i + 1<<": ";
        cin>>request[i];
    }

    int no_of_frames;
    cout<<"Enter the no. of frames: ";
    cin>>no_of_frames;

    lru_algorithm(no_of_pages, request, no_of_frames);
    return 0;
}