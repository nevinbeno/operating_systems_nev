#include <iostream>
#include <deque>
#include <vector>
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
    bool touched;
    bool first_processing;
};

bool compare_at(const struct process& a, const struct process& b)
{
    return a.at < b.at;
}

bool compare_rem(const struct process* a, const process* b)
{
    if (a->rem != b->rem)
        return a->rem > b->rem;
    else
        return a->id < b->id;
}

bool compare_id(const struct process& a, const struct process& b)
{
    return a.id < b.id;
}

bool lrtf(vector<struct process>& p)
{
    int n_proc = p.size();
    if (n_proc < 1)
        return false;

    deque<struct process*> q;
    int time = 0, completed = 0;

    for (int i = 0; i < n_proc; i++)
    {
        p[i].rem = p[i].bt;
        p[i].touched = false;
        p[i].first_processing = true;
        if (p[i].rem == 0)
            completed++;
    }

    sort(p.begin(), p.end(), compare_at);
    time += p[0].at;

    while(completed < n_proc)
    {
        for (int i = 0; i < n_proc; i++)
            if (p[i].at <= time && p[i].touched == false && p[i].rem > 0)
            {
                q.push_back(&p[i]);
                p[i].touched = true;
            }
        if (q.empty())
            time++;
        else
        {
            sort(q.begin(), q.end(), compare_rem);
            struct process* current = q.front();
            current->rem--;
            if (current->first_processing)
            {
                current->first_processing = false;
                current->rt = time - current->at;
            }
            time++;
            if (current->rem == 0)
            {
                current->ct = time;
                current->tat = current->ct - current->at;
                current->wt = current->tat - current->bt;
                q.pop_front();
                completed++;
            }
        }
    }

    return true;
}

void display(vector<struct process>& p)
{
    sort(p.begin(), p.end(), compare_id);
    int total_elements = p.size();
    cout<<"== Longest Remaining Time First =="<<endl;
    cout<<"PID\tAT\tBT\tCT\tTAT\tWT\tResponse Time"<<endl;
    for (int i = 0; i < total_elements; i++)
        cout<<p[i].id<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<"\t"<<p[i].rt<<endl;
    return;
}

int main ()
{
    vector<struct process> p;
    int n;
    cout<<"Enter the no. of processes: ";
    cin>>n;

    cout<<"Enter those process details: "<<endl;
    for (int i = 0; i < n; i ++)
    {
        struct process temp;
        temp.id = i;
        cout<<"Process "<<i<<": "<<endl;
        cout<<"Arrival time: ";
        cin>>temp.at;
        cout<<"Burst time: ";
        cin>>temp.bt;
        p.push_back(temp);
        cout<<endl;
    } 

    bool answer = lrtf(p);

    cout<<endl;

    if (answer)
        display(p);
    else
        cout<<"Error occurred.."<<endl;
    return 0;
}