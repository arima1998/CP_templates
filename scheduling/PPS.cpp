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

void showQ(priority_queue<pii , vector<pii>,compare>q)
{
    while(!q.empty())
    {
        cout<<"("<<q.top().ff<<" "<<q.top().ss<<" )";
        q.pop();
    }
    cout<<endl;
}

int main()
{

    int n;
    cout<<"Input number of process: ";
    cin>>n;
    int burstTime[n+1],arrivalTime[n+1];
    int waitingTime[n+1],turnaroundTime[n+1];
    int startTime[n+1],endTime[n+1],responseTime[n+1],timeQuantum;
    int priorityNumber[n+1];
    vector<pair<int,int>>process;
    vector<pii>granttChart;
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
//    for(int i=1;i<=n;i++)cin>>burstTime[i];
//    for(int i=1;i<=n;i++)cin>>priorityNumber[i];


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


}
