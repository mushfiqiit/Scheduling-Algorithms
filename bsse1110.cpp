#include <bits/stdc++.h>

using namespace std;

struct process{
int index, arrival, burst, priority;
process(int index, int arrival, int burst, int priority)
    :index(index), arrival(arrival), burst(burst), priority(priority)
    {
    }
};

struct compareSJF{
bool operator()(process p1, process p2)
{
    return p1.burst>p2.burst;
}
};

int main()
{
    int priority[7]={0, 8, 3, 4, 4, 5, 5};
    int burst[7]={0, 15, 20, 20, 20, 5, 15};
    int arrival[7]= {0, 0, 0, 20, 25, 45, 55};
    int waitingTime[7], turnAroundTime[7];
    double averageTurnAround=0.0, averageWaiting=0.0;
    int n=6;

    cout << "First Come First Served Scheduling : " << endl;

    long long int currentTime=0;
    for(int i=1;i<=n;i++)
    {
        cout << "Process " << i << ": " << currentTime << " to " << currentTime+burst[i] << endl;
        waitingTime[i]=currentTime-arrival[i];
        currentTime+=burst[i];
        turnAroundTime[i]=currentTime-arrival[i];
        cout << "Waiting Time " << waitingTime[i] << endl;
        averageTurnAround+=(double)(turnAroundTime[i]);
        averageWaiting+=(double)(waitingTime[i]);
    }
    averageTurnAround=averageTurnAround/(double)(n);
    averageWaiting=averageWaiting/(double)(n);
    cout << "Average Turnaround time is " << averageTurnAround << endl;
    cout << "Average waiting time is " << averageWaiting << endl;

    cout << "\n\n";

    cout << "Shortest Job First Scheduling (Non-preemptive) : " << endl;

    priority_queue<process, vector<process>, compareSJF> pqSJF;
    int i=1;
    averageTurnAround=0.0;
    currentTime=arrival[0];
    while(1)
    {
        if(i<=n)
        while(arrival[i]<=currentTime)
        {
            pqSJF.push(process(i, arrival[i], burst[i], priority[i]));
            i++;
            if(i>n)
            {
                break;
            }
        }
        if(pqSJF.empty())
        {
            if(i>n)
            {
                break;
            }

            else
            {
                currentTime=arrival[i];
                continue;
            }
        }
        process temp=pqSJF.top();
        pqSJF.pop();
        waitingTime[temp.index]=currentTime-temp.arrival;
        averageWaiting+=(double)(waitingTime[temp.index]);
        cout << "Process " << temp.index << ": " << currentTime << " to " << currentTime+temp.burst << endl;
        currentTime+=temp.burst;
        turnAroundTime[temp.index]=currentTime-temp.arrival;
        cout << "Waiting time : " << waitingTime[temp.index] << endl;
        averageTurnAround+=(double)(turnAroundTime[temp.index]);
        //cout << turnAroundTime[temp.index] << endl;
    }
    //cout << "Total " << averageTurnAround << endl;
    averageTurnAround=averageTurnAround/(double)(n);
    averageWaiting=averageWaiting/(double)(n);
    cout << "Average turnaround time is " << averageTurnAround << endl;
    cout << "Average waiting time is " << averageWaiting << endl;

    cout << "\n\n";

    cout << "Shortest Job First Scheduling (Preemptive) : " << endl;

    while(!pqSJF.empty())
    {
        pqSJF.pop();
    }

    i=1;
    currentTime=arrival[0];
    int remainingTime;
    int finish[n+1];
    averageTurnAround=0.0;
    averageWaiting=0.0;
    while(i<=n)
    {
        while(arrival[i]<=currentTime)
        {
            pqSJF.push(process(i, arrival[i], burst[i], priority[i]));
            i++;
            if(i>n)
            {
                break;
            }
        }
        if(i>n)
        {
            break;
        }

        process temp=pqSJF.top();
        pqSJF.pop();
        remainingTime=min(arrival[i]-currentTime, (long long int)temp.burst);
        cout << "Process " << temp.index << ": " << currentTime << " to " << currentTime+remainingTime << endl;
        temp.burst-=remainingTime;
        currentTime+=remainingTime;
        if(temp.burst!=0)
        {
            pqSJF.push(process(temp.index, temp.arrival, temp.burst, temp.priority));
        }

        else
        {
            finish[temp.index]=currentTime;
        }
    }

    while(!pqSJF.empty())
    {
        process temp=pqSJF.top();
        pqSJF.pop();
        cout << "Process " << temp.index << ": " << currentTime << " to " << currentTime+temp.burst << endl;
        currentTime+=temp.burst;
        finish[temp.index]=currentTime;
    }

    for(int i=1;i<=n;i++)
    {
        turnAroundTime[i]=finish[i]-arrival[i];
        averageTurnAround+=(double)(turnAroundTime[i]);
        waitingTime[i]=turnAroundTime[i]-burst[i];
        averageWaiting+=(double)(waitingTime[i]);
        cout << "Waiting time for process " << i << " is " << waitingTime[i] << endl;
    }
    averageTurnAround=averageTurnAround/(double)(n);
    averageWaiting=averageWaiting/(double)(n);
    cout << "Average turnaround time is " << averageTurnAround << endl;
    cout << "Average waiting time is " << averageWaiting << endl;

    cout << "\n\n";

    cout << "Round Robin Scheduling :" << endl;
}
