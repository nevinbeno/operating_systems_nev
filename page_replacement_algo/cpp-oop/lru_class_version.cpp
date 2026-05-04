#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;

class LRU
{
    private: 
        int total_no_of_req;
        int no_misses;
        int frames;
        list<int> dll;
        unordered_map<int, list<int>::iterator> hash_table;

    public:
        LRU(int no_of_frames)
        {
            if (no_of_frames < 1)
                throw invalid_argument("Error: The number of frames must be a positive integral");
            frames = no_of_frames;
            no_misses = 0;
            total_no_of_req = 0;
        }
        void access(int key)
        {
            total_no_of_req++;
            auto it = hash_table.find(key);
            if (it != hash_table.end())
            {
                dll.splice(dll.begin(), dll, it->second);
                it->second = dll.begin();
            }
            else
            {
                no_misses++;
                if (dll.size() >= frames)
                {
                    hash_table.erase(dll.back());
                    dll.pop_back();                    
                }
                dll.push_front(key);
                hash_table[key] = dll.begin();
            }
        }
        vector<int> get_frame_state() const
        {
            return vector<int>(dll.begin(), dll.end());
        }
        int get_misses() const
        {
            return no_misses;
        }
        int get_hits() const
        {
            return total_no_of_req - no_misses;
        }
        int get_total_requests_made() const
        {
            return total_no_of_req;
        }
        int get_no_of_frames_allotted() const
        {
            return dll.size();
        }
};

int main()
{
    LRU cache(3);
    int n;
    for (int i = 0; i < 7; i++)
    {
        cout<<"Enter element "<<i + 1<<": ";
        cin>>n;
        cache.access(n);
    }

    cout<<"Final configuration: "<<endl;
    vector<int> arr = cache.get_frame_state();
    for (int x: arr)
        cout<<x<<" ";
    cout<<endl;
    
    cout<<"Total no of requests: "<<cache.get_total_requests_made()<<endl;
    cout<<"Total no of misses: "<<cache.get_misses()<<endl;
    cout<<"Total no of hits: "<<cache.get_hits()<<endl;
    
    return 0;
}