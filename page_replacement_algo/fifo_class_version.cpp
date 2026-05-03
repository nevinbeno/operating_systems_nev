#include <iostream>
#include <unordered_set>
#include <deque>
#include <vector>

using namespace std;

class FIFO
{
    private:
        int no_misses;
        unordered_set<int> s;
        deque<int> q;
        int frames; // no. of frames
        int total_page_requests;
    public:
        FIFO(int no_of_frames)
        {
            if (no_of_frames < 1)
                throw invalid_argument("Frames must be positive. ");
            frames = no_of_frames;
            no_misses = 0; // initializing
            total_page_requests = 0;
        }
        void access(int key) // accesss pages to frames
        {
            total_page_requests++;
            if (s.find(key) == s.end())
            {
                no_misses++;
                if (q.size() >= frames)
                {
                    s.erase(q.front());
                    q.pop_front();
                }
                s.insert(key);
                q.push_back(key);
            }
        }
        vector<int> get_frame_state() const
        {
            return vector<int>(q.begin(), q.end());
        }
        int get_misses() const
        {
            return no_misses;
        }
        int get_hits() const
        {
            return (total_page_requests - no_misses);
        }
        int get_total_requests_made() const
        {
            return total_page_requests;
        }
        int get_no_of_frames_allotted()
        {
            return q.size();
        }
};

int main ()
{
    FIFO cache(3);
    cache.access(8);
    cache.access(1);
    cache.access(7);
    cache.access(6);
    cache.access(8);
    cache.access(7);
    cache.access(8);
    cout<<"The final frame state: "<<endl;
    vector<int> arr = cache.get_frame_state();
    for (int x: arr)
        cout<<x<<" ";
    cout<<endl;
    cout<<"Total no of requests: "<<cache.get_total_requests_made()<<endl;
    cout<<"Total no of misses: "<<cache.get_misses()<<endl;
    cout<<"Total no of hits: "<<cache.get_hits()<<endl;
    

    return 0;
}