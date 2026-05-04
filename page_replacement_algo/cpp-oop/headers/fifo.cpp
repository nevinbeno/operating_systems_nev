#include "fifo.hpp"
#include <stdexcept>

FIFO::FIFO(int no_of_frames)
{
    if (no_of_frames < 1)
        throw std::invalid_argument("Frames must be positive. ");
    frames = no_of_frames;
    no_misses = 0; // initializing
    total_page_requests = 0;
}
void FIFO::access(int key) // accesss pages to frames
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
std::vector<int> FIFO::get_frame_state() const
{
    return std::vector<int>(q.begin(), q.end());
}
int FIFO::get_misses() const
{
    return no_misses;
}
int FIFO::get_hits() const
{
    return (total_page_requests - no_misses);
}
int FIFO::get_total_requests_made() const
{
    return total_page_requests;
}
int FIFO::get_no_of_frames_allotted() const
{
    return q.size();
}