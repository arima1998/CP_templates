#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define ss second
#define ff first

int main()
{
    int n;
    cout<<"Input number of process: ";
    cin>>n;
    int burstTime[n+1],arrivalTime[n+1];
    int waitingTime[n+1],turnaroundTime[n+1];
    int startTime[n+1],endTime[n+1],responseTime[n+1];
    vector<pair<int,int>>process;
    vector<pii>granttChart;
    for(int i=1;i<=n;i++)
    {
        cout<<"Enter Arrival Time of process P"<<i<<": ";
        cin>>arrivalTime[i];
        cout<<"Enter Burst Time of process P"<<i<<": ";
        cin>>burstTime[i];
        process.push_back({arrivalTime[i],i});
        startTime[i]=INT_MAX;
    }
    sort(process.begin(),process.end(),[](pii a,pii b){return a.ff <= b.ff ;});
    int curTime=0;
    int totalidleTime=0;

    for(int i=0;i<n;i++)
    {
        if(arrivalTime[process[i].ss] > curTime)
        {
            int diff=arrivalTime[process[i].ss]-curTime;
            totalidleTime+=diff;
            granttChart.push_back({curTime,-1});
        }
        curTime=max(curTime,arrivalTime[process[i].ss]);
        granttChart.push_back({curTime,process[i].ss});
        startTime[process[i].ss]=min(startTime[process[i].ss],curTime);
        endTime[process[i].ss]=curTime+burstTime[process[i].ss];
        curTime+=burstTime[process[i].ss];
    }
    cout<<"Grantt Chart"<<endl;
    for(pii i:granttChart)
    {
        if(i.ss == -1)
        {
            cout<<i.ff<<" "<<"IDLE ";
        }
        else
        {
            cout<<i.ff<<" P"<<i.ss<<" ";
        }
    }
    cout<<endl;
    cout<<setw(6);
    for(int i=1;i<=n;i++)
    {
        int tt=endTime[i]-arrivalTime[i];
        int wt=tt-burstTime[i];
        waitingTime[i]=wt;
        turnaroundTime[i]=tt;
        responseTime[i]=startTime[i]-arrivalTime[i];
        cout<<"Process: P"<<i<<" Finish time:"<<endTime[i]<<" Response time: "<<startTime[i]-arrivalTime[i]<<" Waiting time: "<<wt<<" Turnaround time: "<<tt<<endl;
    }
    cout<<endl;
    int totalwt=0,totaltt=0;
    for(int i=1;i<=n;i++)
    {
        totalwt+=waitingTime[i];
        totaltt+=turnaroundTime[i];
    }
    cout<<setprecision(3);
    cout<<"Average waiting time : "<<(double)totalwt/(double)n<<endl;
    cout<<"Average turnaround time : "<<(double)totaltt/(double)n<<endl;
    cout<<"Idle time: "<<totalidleTime<<endl;


}
