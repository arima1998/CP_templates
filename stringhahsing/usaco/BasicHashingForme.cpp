class Hashing {
    private:
        static const ll Mod = (1LL << 61) - 1;
        static const ll base;
        static vector<long long>pow;
        vector<long long>p_hash;
        __int128 mul(ll a, ll b) { return (__int128)a * b; }
        ll mod_mul(ll a, ll b) { return mul(a, b) % Mod; }
    public:
        Hashing(const string &s): p_hash(s.size()+1){
            while(pow.size() < s.size()){ pow.push_back(mod_mul(pow.back(), base)); }
            p_hash[0]=0;
            for(int i=0;i<s.size();i++)
            {
                p_hash[i+1]=(mul(p_hash[i], base) + s[i])%Mod;
            }
        }
        /// I used string to be 0 indexed
        long long getHash(int st,int ed)
        {
            long long val=p_hash[ed + 1] - mod_mul(p_hash[st], pow[ed - st + 1]);
            return (val%Mod+Mod)%Mod;
        }

};
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
vector<ll> Hashing::pow = {1};
const ll Hashing::base = uniform_int_distribution<ll>(0, Mod - 1)(rng);
