#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define ss second
#define ff first

struct compare{
    bool operator()(const pii & a, const pii & b)
    {
        return a.ff < b.ff;
    }
};

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

    queue<pii>p;
    for(int i=0;i<n;i++){
        p.push(process[i]);
    }
    priority_queue<pii,vector<pii>,compare>WaitingQ;
    int SUM=0,ELEM=n;
    for(int i=1;i<=n;i++)SUM+=burstTime[i];
    int avg=SUM/n;

    auto TQGEN= [](int avg){
        return avg + (rand()%10);
    };
    int TQ=TQGEN(avg);
    int pTQ=TQ;

    while(!p.empty() or !WaitingQ.empty())
    {
        while(!p.empty() and p.front().ff <=curTime)
        {
            pii P=p.front(); /// p.ff == arrivalTime,p.ss==ID
            p.pop();
            int id=P.ss;
            WaitingQ.push({burstTime[id],id});
        }
        while(WaitingQ.empty())
        {
            pii P=p.front();
            p.pop();
            int id=P.ss;
            int diff=P.ff-curTime;
            if(diff > 0)
            {
                granttChart.push_back({curTime,-1});
                totalidleTime+=diff;
            }
            WaitingQ.push({burstTime[id],id});
        }
        pii P=WaitingQ.top();
        int id=P.ss;
        WaitingQ.pop();
        curTime=max(curTime,arrivalTime[id]);
        startTime[id]=min(startTime[id],curTime);
        granttChart.push_back({curTime,id});
        if(P.ff > pTQ)
        {
            P.ff-=pTQ;
            SUM-=pTQ;
            curTime+=pTQ;
            pTQ=TQ;
            WaitingQ.push(P);
        }
        else
        {
            pTQ-=P.ff;
            SUM-=P.ff;
            curTime+=P.ff;
            endTime[id]=curTime;
            P.ff=0;
            ELEM--;
            if(pTQ == 0){
                avg=SUM/max(ELEM,1);
                pTQ=TQGEN(avg);
            }
        }
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
