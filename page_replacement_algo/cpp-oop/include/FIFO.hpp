#ifndef FIFO_HPP
#define FIFO_HPP

#include <unordered_set>
#include <vector>
#include <deque>

class FIFO
{
    private:
        int no_misses;
        int frames; // no. of frames
        int total_page_requests;
        std::unordered_set<int> s;
        std::deque<int> q;
    public:
        FIFO(int no_of_frames);
        void access(int key);
        std::vector<int> get_frame_state() const;
        int get_misses() const;
        int get_hits() const;
        int get_total_requests_made() const;
        int get_no_of_frames_allotted() const;
};

#endif