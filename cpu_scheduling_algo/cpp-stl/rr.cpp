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
    bool touched;
};

bool compare_at(struct process a, struct process b)
{
    return a.at < b.at;
}

bool compare_id(struct process a, struct process b)
{
    return a.id < b.id;
}

bool rr(vector<struct process>& p, int tq)
{
    if (p.empty())
    {
        cout<<"No processes received"<<endl;
        return false;
    }
    int n_proc = p.size();
    for (int i = 0; i < n_proc; i++)
    {
        p[i].touched = false; // none of these processes were added to the queue
        p[i].rem = p[i].bt;   
    }
    sort(p.begin(), p.end(), compare_at);
    deque<int> q;

    int curr_time = 0;

    int completed = 0;
    while(completed < n_proc)
    {
        for (int i = 0; i < n_proc; i++)
            if (p[i].at <= curr_time && p[i].touched == false)
            {
                q.push_back(i);
                p[i].touched = true;
            }
        if (q.empty())
            curr_time++;
        else
        {
            int index = q.front();
            q.pop_front();
            if (p[index].rem > tq)
            {
                p[index].rem -= tq;
                curr_time += tq;
            }
            else
            {
                curr_time += p[index].rem;
                p[index].rem = 0;
                completed++;
                p[index].ct = curr_time;
                p[index].tat = p[index].ct - p[index].at;
                p[index].wt = p[index].tat - p[index].bt;
            }
            for (int i = 0; i < n_proc; i++)
                if (p[i].at <= curr_time && p[i].touched == false)
                {
                    q.push_back(i);
                    p[i].touched = true;
                }
            if (p[index].rem > 0)
                q.push_back(index);
        }
    }
    return true;
}

void display(vector<struct process>& p, int tq)
{
    sort(p.begin(), p.end(), compare_id);
    int total_elements = p.size();
    cout<<"== Round Robin =="<<endl;
    cout<<"PID\tAT\tBT\tCT\tTAT\tWT"<<endl;
    for (int i = 0; i < total_elements; i++)
        cout<<p[i].id<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<endl;
    return;
}

int main ()
{
    vector<struct process> p;
    int n;
    cout<<"Enter the no. of processes: ";
    cin>>n;

    int tq;

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

    cout<<endl;
    cout<<"Time quantum: ";
    cin>>tq;    

    bool answer = rr(p, tq);

    cout<<endl;

    if (answer)
        display(p, tq);
    else
        cout<<"Error occurred.."<<endl;
    return 0;
}