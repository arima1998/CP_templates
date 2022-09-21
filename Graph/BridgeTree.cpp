/// VARIFIED with https://codeforces.com/contest/1000/submission/172958336


#include<bits/stdc++.h>
using namespace std;
#define lli long long int
#define lld long double
#define ul  unsigned long int
#define pii pair<int,int>
#define pll pair<lli, lli>
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
#define PRINTER(A,N) for(int i=1;i<=N;i++)cout<<A[i]<<" ";
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";}
template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "(" << p.ff << ", " << p.ss << ")"; }
template<typename A>ostream& operator<<(ostream &cout , set<A>const &s){cout<<"[";for(A i:s){cout<<i<<" ";}return cout<<"]";}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) {
	cin >> p.first;
	return cin >> p.second;
}

struct IOSetup {
  IOSetup() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    std::cout << fixed << setprecision(20);
  }
} iosetup;

void PrintBrinary(int a){int f[32]={0};int cur=0;while(a){f[cur]=a%2;a=a/2;cur++;}reverse(f,f+32);for(int i=0;i<32;i++)cout<<f[i];cout<<endl;}
void show(int i){cout<<(i==0? "NO":"YES")<<endl;}
int turnOn(int mask,int pos) {return mask | (1<<pos);}
int turnOff(int mask,int pos){return mask & !(1<<pos);}
bool isOn(int mask,int pos) {return (bool)(mask & (1<<pos));}
lli ceil_value(lli nom,lli denom){return nom/denom + (nom%denom!=0);}
lli biggestPowerOfTwo(lli n){lli res=1;while(res*2<=n){res*=2;}return res;}
const lli maxn = 1e6+10;
const lli INF = 1e18+10;
const lli mod = 1e9 + 7;
int X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };



int n,m; // number of nodes+edges
vector<pii> adj[maxn]; // adjacency list of graph
vector<int>BridgeTree[maxn]; // bridgeTree

vector<bool> visited;
vector<int> tin, low,component,level;
int isBridge[maxn];
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (auto [to,id] : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                isBridge[id]=1;

        }
    }
}

void find_bridges() {
    timer = 0;
    visited.assign(n+1, false);
    tin.assign(n+1, -1);
    low.assign(n+1, -1);
    for (int i = 1; i <=n; ++i) {
        if (!visited[i])
            dfs(i);
    }

}

void ConstructBridgeTree(int u,int c)
{
    component[u]=c;
    visited[u]=true;
    for(auto [v,id] : adj[u])
    {
        if(isBridge[id] ==  1)continue;
        if(visited[v] ==0 )
        {
            ConstructBridgeTree(v,c);
        }
    }

}
int ComputeLevel(int s)
{
    visited.assign(n+1,false);
    queue<int>q;
    visited[s]=1;
    level.assign(n+1,0);

    q.push(s);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int v:BridgeTree[u])
        {
            if(visited[v]==0)
            {
                level[v]=level[u]+1;
                visited[v]=1;
                q.push(v);
            }
        }
    }
    pii maxNode={0,0};
    for(int i=1;i<=n;i++)
    {
        if(level[i] > maxNode.ff)
        {
            maxNode={level[i],i};
        }
    }
    return maxNode.ss;

}

void solve()
{
    cin>>n>>m;
    vector<pii>edges;
    edges.pb({-1,-1});
    for(int i=1;i<=m;i++)
    {
        int a,b;cin>>a>>b;
        adj[a].pb({b,i});
        adj[b].pb({a,i});
        edges.push_back({a,b});
    }
    find_bridges();
    visited.assign(n+1,false);
    component.assign(n+1,0);
    int c=0;
    for(int i=1;i<=n;i++)
    {
        if(visited[i] == 0)
        {
            c++;
            ConstructBridgeTree(i,c);
        }
    }
    for(int i=1;i<=m;i++)
    {
        if(isBridge[i] ==  1)
        {
            int a,b;
            a=edges[i].ff;
            b=edges[i].ss;
            BridgeTree[component[a]].pb(component[b]);
            BridgeTree[component[b]].pb(component[a]);
        }
    }
    int NODE1=ComputeLevel(1);
    int NODE2=ComputeLevel(NODE1);
    cout<<level[NODE2]<<endl;

}

int main()
{
    solve();
}
/**
7
8
1 2
2 3
3 1
2 4
2 5
2 7
4 6
5 6
**/
