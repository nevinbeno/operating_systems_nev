#include <iostream>
#include <deque>
#include <unordered_set>
#include <vector>

using namespace std;

void fifo(int pages, vector<int>& req, int frames)
{
    unordered_set<int> s;
    deque<int> q;
    int no_misses = 0;
    for (int i = 0; i < pages; i++)
    {
        int key = req[i];
        if (s.find(key) == s.end()) // if miss
        {
            no_misses++;
            if (q.size() >= frames)
            {
                int pop_page = q.front();
                q.pop_front();
                s.erase(pop_page);
            }
            s.insert(key);
            q.push_back(key);
        }
    }
    cout<<"The total no. of page requests: "<<pages<<endl;
    cout<<"Total no of page faults: "<<no_misses<<endl;
    cout<<"Total no of hits: "<<pages - no_misses<<endl;
    cout<<"The final configuration: "<<endl;
    for (int element: q)
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

    fifo(no_of_pages, request, no_of_frames);
    return 0;
}