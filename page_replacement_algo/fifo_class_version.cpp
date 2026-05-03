#include <iostream>
#include <unordered_set>
#include <deque>

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
        void allocate(int key) // allocates pages to frames
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
        void display_current_frame_state() const
        {
            cout<<"Current configuration of Frames: "<<endl;
            if (q.empty())
                cout<<"Empty; No frame is allotted to any page.";
            else
            {
                for (int element: q)
                    cout<<element<<" ";
            }
            cout<<endl;
        }
        void display_current_status() const
        {
            cout<<"The current status (Total request, Misses, Hits)"<<endl;
            cout<<"Total no of pages requested: "<<total_page_requests<<endl;
            cout<<"Total misses: "<<no_misses<<endl;
            cout<<"Total hits: "<<total_page_requests - no_misses<<endl;
        }
};

int main ()
{
    FIFO cache(3);
    cache.display_current_frame_state();
    cache.display_current_status();
    cache.allocate(8);
    cache.allocate(1);
    cache.allocate(7);
    cache.allocate(6);
    cache.allocate(8);
    cache.allocate(7);
    cache.allocate(8);
    cache.display_current_frame_state();
    cache.display_current_status();
    return 0;
}