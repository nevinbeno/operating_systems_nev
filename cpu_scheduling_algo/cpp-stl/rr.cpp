#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

struct process
{
    int id;
    int at;
    int bt;
    int rem;
    int ct;
    int tat;
    int wt;
    int rt;
    bool status;
};

bool compare(struct process a, struct process b)
{
    return a.at < b.at;
}

bool rr(vector<struct process>& p, int tq)
{
    if (p.empty())
    {
        cout<<"No processes received"<<endl;
        return false;
    }
    int n_proc = p.size();
    sort(p.begin(), p.end(), compare);
    deque<struct process> q;

    int curr_time = 0;
    curr_time += p[0].at;

}