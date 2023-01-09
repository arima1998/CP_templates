const int MAX = 1e7;
bool vis[MAX];
int sp[MAX];



void Sieve(){
	for (int i = 2; i < MAX; i += 2)	sp[i] = 2;
	for (lli i = 3; i < MAX; i += 2){
		if (!vis[i]){
			sp[i] = i;
			for (lli j = i; (j*i) < MAX; j += 2){
				if (!vis[j*i])	vis[j*i] = true, sp[j*i] = i;
			}
		}
	}
}

vector<int>factorization(int n)
{
    vector<int> res;
    while (n!=1)
    {
        res.push_back(sp[n]);
        n=n/sp[n];
    }
    return res;
}
