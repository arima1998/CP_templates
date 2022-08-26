//// 1804113-CSE-CUET


#include<bits/stdc++.h>
using namespace std;
#define lli long long int
#define lld long double
#define ul  unsigned long int
#define pii pair<int,int>
#define pll pair<lli, lli>
#define piii pair<pii,pii>
#define vi  vector<int>
#define vii vector<pair<int,int>>
#define vll vector<lli>
#define pb  push_back
#define mpr  make_pair
#define ss second
#define ff first
#define pie 3.14159265358979323846264338327950L
#define all(x) x.begin(),x.end()
#define testcase() int tc;cin>>tc;while(tc--)
#define clean(x,y) memset(x,y,sizeof(x))
#define getunique(v) {sort(all(v)); v.erase(unique(all(v)), v.end());}
#define loop(i,st,ed) for(int i=st;i<=ed;i++)
#define debug cout<<"HERE is ok"<<endl
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "(" << p.ff << ", " << p.ss << ")"; }
template<typename A>ostream& operator<<(ostream &cout , set<A>const &s){cout<<"[";for(A i:s){cout<<i<<" ";}return cout<<"]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) {
	cin >> p.first;
	return cin >> p.second;
}
const int maxn = 100;

int n;
int burstTime[maxn],arrivalTime[maxn];
int waitingTime[maxn],turnaroundTime[maxn];
int startTime[maxn],endTime[maxn],responseTime[maxn],timeQuantum;
int priorityNumber[maxn];
vector<pair<int,int>>process;
vector<pii>granttChart;

int globalTrigger=0;

void ignoreCout()
{
    cout.setstate(ios_base::failbit);
}

void input(int choice)
{
    if(globalTrigger == 1)
    {
        ignoreCout();
        return;
    }
    process.clear();
    granttChart.clear();
    cout<<"Input number of process: ";
    cin>>n;
    if(choice <= 3)
    {
        for(int i=1;i<=n;i++)
        {
            cout<<"Enter Arrival Time of process P"<<i<<": ";
            cin>>arrivalTime[i];
            cout<<"Enter Burst Time of process P"<<i<<": ";
            cin>>burstTime[i];
            process.push_back({arrivalTime[i],i});
            startTime[i]=INT_MAX;
        }
    }
    else if(choice <=5)
    {
        for(int i=1;i<=n;i++)
        {
            cout<<"Enter Arrival Time of P"<<i<<": ";
            cin>>arrivalTime[i];
            cout<<"Enter Burst Time of P"<<i<<": ";
            cin>>burstTime[i];
            cout<<"Enter Priority of P"<<i<<": ";
            cin>>priorityNumber[i];
            process.push_back({arrivalTime[i],i});
            startTime[i]=INT_MAX;
        }
    }
    else if(choice == 6)
    {
        for(int i=1;i<=n;i++)
        {
            cout<<"Enter Arrival Time of P"<<i<<": ";
            cin>>arrivalTime[i];
            cout<<"Enter Burst Time of P"<<i<<": ";
            cin>>burstTime[i];
            process.push_back({arrivalTime[i],i});
            startTime[i]=INT_MAX;
        }
        cout<<"Enter Time Quantum: "<<endl;
        cin>>timeQuantum;
    }
    else if(choice == 7){
        for(int i=1;i<=n;i++)
        {
            cout<<"Enter Arrival Time of P"<<i<<": ";
            cin>>arrivalTime[i];
            cout<<"Enter Burst Time of P"<<i<<": ";
            cin>>burstTime[i];
            process.push_back({arrivalTime[i],i});
            startTime[i]=INT_MAX;
        }
    }
}

struct compare{
    bool operator()(const pii & a, const pii & b)
    {
        return a.ff > b.ff;
    }
};

struct comparePriority{

    /// arrival burst id priority

    bool operator()(const piii & a, const piii & b)
    {
        if(a.ss.ss != b.ss.ss)return a.ss.ss > b.ss.ss;
        else
        {
            return a.ff.ff > b.ff.ff;
        }
    }
};

pair<double,double> FCFS()
{
    input(1);
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
    return {(double)totalwt/(double)n,(double)totaltt/(double)n};
}

pair<double,double>SJF()
{
    input(2);
    sort(process.begin(),process.end(),[](pii a,pii b){return a.ff <= b.ff ;});
    int curTime=0;
    int totalidleTime=0,done=0,vis[n+1]={0};
    priority_queue<pii , vector<pii>,compare>currentProcess;
    cout<<process<<endl;

    while(1)
    {
        if(done == n)break;
        if(currentProcess.empty())
        {
            for(int i=0;i<n;i++)
            {
                int id=process[i].ss;
                if(vis[id] == 0)
                {
                    vis[id]=1;
                    currentProcess.push({burstTime[id],id});
                    break;
                }
            }
        }

        pii job=currentProcess.top();
        currentProcess.pop();
        int id=job.ss;
        int remTime=job.ff;

        if(curTime < arrivalTime[id])
        {
            int diff=arrivalTime[id]-curTime;
            totalidleTime+=diff;
            granttChart.push_back({curTime,-1});
        }
        curTime=max(curTime,arrivalTime[id]);

        startTime[id]=min(curTime,startTime[id]);
        granttChart.pb({curTime,id});
        curTime+=remTime;
        remTime=0;
        endTime[id]=curTime;
        for(int k=0;k<n;k++)
        {
            int id_=process[k].ss;
            if(vis[id_] == 0 and process[k].ff <= curTime)
            {
                vis[id_]=1;
                currentProcess.push({burstTime[id_],id_});
            }
        }
        done++;
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
    return {(double)totalwt/(double)n,(double)totaltt/(double)n};
}
pair<double,double>SRTF()
{
    input(3);
    sort(process.begin(),process.end(),[](pii a,pii b){return a.ff <= b.ff ;});
    int curTime=0;
    int totalidleTime=0,done=0,vis[n+1]={0};
    priority_queue<pii , vector<pii>,compare>currentProcess;

    while(1)
    {
        if(done == n)break;
        if(currentProcess.empty())
        {
            for(int i=0;i<n;i++)
            {
                int id=process[i].ss;
                if(vis[id] == 0)
                {
                    vis[id]=1;
                    currentProcess.push({burstTime[id],id});
                    break;
                }
            }
        }

        pii job=currentProcess.top();
        currentProcess.pop();
        int id=job.ss;
        int remTime=job.ff;

        if(curTime < arrivalTime[id])
        {
            int diff=arrivalTime[id]-curTime;
            totalidleTime+=diff;
            granttChart.push_back({curTime,-1});
        }
        curTime=max(curTime,arrivalTime[id]);

        startTime[id]=min(curTime,startTime[id]);
        granttChart.pb({curTime,id});
        curTime++;
        remTime--;
        endTime[id]=curTime;
        for(int k=0;k<n;k++)
        {
            int id_=process[k].ss;
            if(vis[id_] == 0 and process[k].ff <= curTime)
            {
                vis[id_]=1;
                currentProcess.push({burstTime[id_],id_});
            }
        }
        if(remTime > 0)currentProcess.push({remTime,id});
        else done++;
    }
    vector<pii>newGranttChart;
    newGranttChart.pb(granttChart[0]);
    for(int i=1;i<granttChart.size();i++)
    {
        if(granttChart[i].ss == granttChart[i-1].ss )continue;
        else
        {
            newGranttChart.pb(granttChart[i]);
        }
    }
    granttChart.clear();
    granttChart=newGranttChart;

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
    return {(double)totalwt/(double)n,(double)totaltt/(double)n};
}
pair<double,double>NPPS()
{
    input(4);
    sort(process.begin(),process.end(),[](pii a,pii b){return a.ff <= b.ff ;});
    int curTime=0;
    int totalidleTime=0,done=0,vis[n+1]={0};
    priority_queue<piii , vector<piii>,comparePriority>currentProcess;
    cout<<process<<endl;

    while(1)
    {
        if(done == n)break;
        if(currentProcess.empty())
        {
            for(int i=0;i<n;i++)
            {
                int id=process[i].ss;
                if(vis[id] == 0)
                {
                    vis[id]=1;
                    currentProcess.push({{arrivalTime[id],burstTime[id]},{id,priorityNumber[id]}});
                    break;
                }
            }
        }

        piii job=currentProcess.top();
        currentProcess.pop();
        int id=job.ss.ff;
        int remTime=job.ff.ss;

        if(curTime < arrivalTime[id])
        {
            int diff=arrivalTime[id]-curTime;
            totalidleTime+=diff;
            granttChart.push_back({curTime,-1});
        }
        curTime=max(curTime,arrivalTime[id]);

        startTime[id]=min(curTime,startTime[id]);
        granttChart.pb({curTime,id});
        curTime+=remTime;
        remTime=0;
        endTime[id]=curTime;
        for(int k=0;k<n;k++)
        {
            int id_=process[k].ss;
            if(vis[id_] == 0 and process[k].ff <= curTime)
            {
                vis[id_]=1;
                currentProcess.push({{arrivalTime[id_],burstTime[id_]},{id_,priorityNumber[id_]}});
            }
        }
        if(remTime > 0)currentProcess.push({{arrivalTime[id],remTime},{id,priorityNumber[id]}});
        else done++;
    }
    vector<pii>newGranttChart;
    newGranttChart.pb(granttChart[0]);
    for(int i=1;i<granttChart.size();i++)
    {
        if(granttChart[i].ss == granttChart[i-1].ss )continue;
        else
        {
            newGranttChart.pb(granttChart[i]);
        }
    }
    granttChart.clear();
    granttChart=newGranttChart;

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
    return {(double)totalwt/(double)n,(double)totaltt/(double)n};
}
pair<double,double>PPS()
{
    input(5);
    sort(process.begin(),process.end(),[](pii a,pii b){return a.ff <= b.ff ;});
    int curTime=0;
    int totalidleTime=0,done=0,vis[n+1]={0};
    priority_queue<piii , vector<piii>,comparePriority>currentProcess;
    while(1)
    {
        if(done == n)break;
        if(currentProcess.empty())
        {
            for(int i=0;i<n;i++)
            {
                int id=process[i].ss;
                if(vis[id] == 0)
                {
                    vis[id]=1;
                    currentProcess.push({{arrivalTime[id],burstTime[id]},{id,priorityNumber[id]}});
                    break;
                }
            }
        }

        piii job=currentProcess.top();
        currentProcess.pop();
        int id=job.ss.ff;
        int remTime=job.ff.ss;

        if(curTime < arrivalTime[id])
        {
            int diff=arrivalTime[id]-curTime;
            totalidleTime+=diff;
            granttChart.push_back({curTime,-1});
        }
        curTime=max(curTime,arrivalTime[id]);

        startTime[id]=min(curTime,startTime[id]);
        granttChart.pb({curTime,id});
        curTime++;
        remTime--;
        endTime[id]=curTime;
        for(int k=0;k<n;k++)
        {
            int id_=process[k].ss;
            if(vis[id_] == 0 and process[k].ff <= curTime)
            {
                vis[id_]=1;
                currentProcess.push({{arrivalTime[id_],burstTime[id_]},{id_,priorityNumber[id_]}});
            }
        }
        if(remTime > 0)currentProcess.push({{arrivalTime[id],remTime},{id,priorityNumber[id]}});
        else done++;
    }
    vector<pii>newGranttChart;
    newGranttChart.pb(granttChart[0]);
    for(int i=1;i<granttChart.size();i++)
    {
        if(granttChart[i].ss == granttChart[i-1].ss )continue;
        else
        {
            newGranttChart.pb(granttChart[i]);
        }
    }
    granttChart.clear();
    granttChart=newGranttChart;

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
    return {(double)totalwt/(double)n,(double)totaltt/(double)n};
}
pair<double,double>RR()
{
    input(6);
    sort(process.begin(),process.end(),[](pii a,pii b){return a.ff <= b.ff ;});
    int curTime=0;
    int totalidleTime=0,pTQ=timeQuantum;
    queue<pii>currentProcess;
    bool vis[n+1]={0};
    int done=0;

    while(1)
    {
        if(done == n)break;
        if(currentProcess.empty())
        {
            for(int i=0;i<n;i++)
            {
                int id=process[i].ss;
                if(vis[id] == false)
                {
                    currentProcess.push({burstTime[id],id});
                    vis[id]=1;
                    break;
                }
            }
        }
        pii job=currentProcess.front();
        currentProcess.pop();
        int id=job.ss;
        if(curTime<arrivalTime[id])
        {
            int diff=arrivalTime[id]-curTime;
            totalidleTime+=diff;
            granttChart.pb({curTime,-1});
        }
        curTime=max(arrivalTime[id],curTime);
        startTime[id]=min(startTime[id],curTime);
        granttChart.pb({curTime,id});
        int remTime=job.ff;
        if(remTime > pTQ)
        {
            curTime+=pTQ;
            remTime-=pTQ;
            pTQ=timeQuantum;
        }
        else{
            curTime+=remTime;
            remTime=0;
            done++;
            pTQ=timeQuantum;
        }
        endTime[id]=curTime;
        for(int k=0;k<n;k++)
        {
            int id_=process[k].ss;
            if(vis[id_] == false and arrivalTime[id_] <=  curTime)
            {
                currentProcess.push({burstTime[id_],id_});
                vis[id_]=1;
            }
        }
        if(remTime > 0)
        {
            currentProcess.push({remTime,id});
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
    return {(double)totalwt/(double)n,(double)totaltt/(double)n};
}
pair<double,double>MRR()
{
    input(7);
    int totalSum=0;
    for(int i=1;i<=n;i++)totalSum+=burstTime[i];
    int elem=n;

   auto TQGEN= [](int avg){
        return avg + (rand()%10);
    };
    timeQuantum=TQGEN(totalSum/elem);

    sort(process.begin(),process.end(),[](pii a,pii b){return a.ff <= b.ff ;});
    int curTime=0;
    int totalidleTime=0,pTQ=timeQuantum;
    queue<pii>currentProcess;
    bool vis[n+1]={0};
    int done=0;



    while(1)
    {
        if(done == n)break;
        if(currentProcess.empty())
        {
            for(int i=0;i<n;i++)
            {
                int id=process[i].ss;
                if(vis[id] == false)
                {
                    currentProcess.push({burstTime[id],id});
                    vis[id]=1;
                    break;
                }
            }
        }
        pii job=currentProcess.front();
        currentProcess.pop();
        int id=job.ss;
        if(curTime<arrivalTime[id])
        {
            int diff=arrivalTime[id]-curTime;
            totalidleTime+=diff;
            granttChart.pb({curTime,-1});
        }
        curTime=max(arrivalTime[id],curTime);
        startTime[id]=min(startTime[id],curTime);
        granttChart.pb({curTime,id});
        int remTime=job.ff;
        if(remTime > pTQ)
        {
            curTime+=pTQ;
            remTime-=pTQ;
            totalSum-=pTQ;
            pTQ=timeQuantum;
        }
        else{
            curTime+=remTime;
            totalSum-=remTime;
            remTime=0;
            done++;
            elem--;
            elem=max(1,elem);
            pTQ=TQGEN(totalSum/elem);
        }
        endTime[id]=curTime;
        for(int k=0;k<n;k++)
        {
            int id_=process[k].ss;
            if(vis[id_] == false and arrivalTime[id_] <=  curTime)
            {
                currentProcess.push({burstTime[id_],id_});
                vis[id_]=1;
            }
        }
        if(remTime > 0)
        {
            currentProcess.push({remTime,id});
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
    return {(double)totalwt/(double)n,(double)totaltt/(double)n};
}

void CompareAll()
{
    cout<<"Input number of process: ";
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cout<<"Enter Arrival Time of P"<<i<<": ";
        cin>>arrivalTime[i];
        cout<<"Enter Burst Time of P"<<i<<": ";
        cin>>burstTime[i];
        cout<<"Enter Priority of P"<<i<<": ";
        cin>>priorityNumber[i];
        process.push_back({arrivalTime[i],i});
        startTime[i]=INT_MAX;
    }
    cout<<"Enter Time Quantum: "<<endl;
    cin>>timeQuantum;
    globalTrigger=1;
    cout<<setprecision(6)<<setw(6);
    auto ans1=FCFS();
    cout.clear();
    cout<<"Algorithm: 1    Average Waiting Time: "<<ans1.ff<<" Average Turnaround Time: "<<ans1.ss<<endl;
    ignoreCout();
    auto ans2=SJF();
    cout.clear();
    cout<<"Algorithm: 2    Average Waiting Time: "<<ans2.ff<<" Average Turnaround Time: "<<ans2.ss<<endl;
    ignoreCout();
    auto ans3=SRTF();
    cout.clear();
    cout<<"Algorithm: 3    Average Waiting Time: "<<ans3.ff<<" Average Turnaround Time: "<<ans3.ss<<endl;
    ignoreCout();
    auto ans4=NPPS();
    cout.clear();
    cout<<"Algorithm: 4    Average Waiting Time: "<<ans4.ff<<" Average Turnaround Time: "<<ans4.ss<<endl;
    ignoreCout();
    auto ans5=PPS();
    cout.clear();
    cout<<"Algorithm: 5    Average Waiting Time: "<<ans5.ff<<" Average Turnaround Time: "<<ans5.ss<<endl;
    ignoreCout();
    auto ans6=RR();
    cout.clear();
    cout<<"Algorithm: 6    Average Waiting Time: "<<ans6.ff<<" Average Turnaround Time: "<<ans6.ss<<endl;
    ignoreCout();
    auto ans7=MRR();
    cout.clear();
    cout<<"Algorithm: 7    Average Waiting Time: "<<ans7.ff<<" Average Turnaround Time: "<<ans7.ss<<endl;
}

int main()
{
    srand(time(0));
    int op;
    while(1)
    {
        cout<<"1: FCFS"<<endl;
        cout<<"2: Non-Preemptive-SJF"<<endl;
        cout<<"3: Preemptive-SJF"<<endl;
        cout<<"4: Non-Preemptive-Priority"<<endl;
        cout<<"5: Preemptive-Priority"<<endl;
        cout<<"6: Round-Robin"<<endl;
        cout<<"7: Our-Proposed-Algorithm"<<endl;
        cout<<"8: Compare-All"<<endl;
        cout<<"9: Exit"<<endl;
        cout<<"Input Your Choice: ";
        cin>>op;
        if(op == 9)break;
        if(op == 1)
        {
            auto ans=FCFS();
        }
        else if(op==2)
        {
            auto ans=SJF();
        }
        else if(op==3)
        {
            auto ans=SRTF();
        }
        else if(op==4)
        {
            auto ans=NPPS();
        }
        else if(op==5)
        {
            auto ans=PPS();
        }
        else if(op==6)
        {
            auto ans=RR();
        }
        else if(op==7)
        {
            auto ans=MRR();
        }
        else if(op==8)
        {
            CompareAll();
        }
    }
}
