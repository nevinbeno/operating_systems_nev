#ifndef LRU_HPP
#define LRU_HPP

#include <unordered_map>
#include <vector>
#include <list>

class LRU
{
    private:
        std::list<int> dll;
        std::unordered_map<int, std::list<int>::iterator> hash_table;
        int total_page_requests;
        int no_misses;
        int frames;
    public:
        LRU(int no_of_frames);
        void access(int key);
        std::vector<int> get_frame_state() const;
        int get_misses() const;
        int get_hits() const;
        int get_total_requests_made() const;
        int get_no_of_frames_allotted() const;
};

#endif