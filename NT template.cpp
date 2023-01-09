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

///----------------------------------------- Sieve Factor ----------------------------------------

bool vis[maxn];

void Sieve(){
    memset(vis, true, sizeof(vis));

    vis[0] = vis[1] = false;
    for(int i = 4 ; i < maxn ; i += 2)
        vis[i] = false;
    for(int i = 3 ; i < maxn / i ; i += 2){
        if(!vis[i])continue;
        for(int j = i * i ; j < maxn ; j += i + i)
            vis[j] = false;
    }
}

vector<int> primes;

void Gen(){
    for(int i = 2 ; i < maxn ; ++i)
        if(vis[i])
            primes.emplace_back(i);
}

/// --------------------------------------- Sieve ---------------- can factor 1E9 fast {<=SQRT(1E9)}
