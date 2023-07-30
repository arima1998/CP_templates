class Hashing {
    private:
        static const long long Mod = 1e9+9;
        static const long long base = 31;
        static vector<long long>pow;
        vector<long long>p_hash;
    public:
        Hashing(const string &s): p_hash(s.size()+1){
            while(pow.size() < s.size()){pow.push_back((pow.back() * base)%Mod);}
            p_hash[0]=0;
            for(int i=0;i<s.size();i++)
            {
                p_hash[i+1]=((p_hash[i]*base)%Mod + s[i])%Mod;
            }
        }
        /// I used string to be 0 indexed
        long long getHash(int st,int ed)
        {
            long long val=(p_hash[ed+1]-(p_hash[st]*pow[ed-st+1]));
            return (val%Mod+Mod)%Mod;
        }
        
};
/// Hashing h1(s) ..to start
vector<long long>Hashing::pow={1};
