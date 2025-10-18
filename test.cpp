// test.cpp
// ACM 竞赛常用模板
// 快速输入输出、常用数据结构和算法骨架

#include <bits/stdc++.h>
using namespace std;

// 类型别名
using ll = long long;
using ull = unsigned long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;

// 常用宏
#define rep(i,a,b) for(int i=(a); i<(b); ++i)
#define per(i,a,b) for(int i=(b)-1; i>=(a); --i)
#define all(x) (x).begin(), (x).end()
#define sz(x) int((x).size())
template<class T> inline bool chmin(T &a, const T &b){ if(b<a){ a=b; return true;} return false; }
template<class T> inline bool chmax(T &a, const T &b){ if(b>a){ a=b; return true;} return false; }

// 快速IO
struct FastIO {
    FastIO(){ ios::sync_with_stdio(false); cin.tie(nullptr); }
} fastio;

// 常用数学工具
ll gcdll(ll a, ll b){ while(b){ ll t = a % b; a = b; b = t; } return abs(a); }
ll lcmll(ll a, ll b){ return a / gcdll(a,b) * b; }
ll modpow(ll a, ll e, ll mod){
    a %= mod; ll r = 1;
    while(e){ if(e&1) r = (__int128)r*a%mod; a = (__int128)a*a%mod; e >>= 1; }
    return r;
}
ll modinv(ll a, ll mod){ // mod must be prime or a coprime
    return modpow((a%mod+mod)%mod, mod-2, mod);
}

// DSU (并查集)
struct DSU {
    int n;
    vector<int> p, r;
    DSU(int n=0){ init(n); }
    void init(int n_){ n=n_; p.resize(n); r.assign(n,0); iota(p.begin(), p.end(), 0); }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a;
        if(r[a]==r[b]) r[a]++;
        return true;
    }
    bool same(int a,int b){ return find(a)==find(b); }
};

// Fenwick 树 / BIT
template<class T>
struct Fenwick {
    int n; vector<T> bit;
    Fenwick(int n=0){ init(n); }
    void init(int n_){ n=n_; bit.assign(n+1,0); }
    void add(int i, T delta){ for(++i;i<=n;i+=i&-i) bit[i]+=delta; }
    T sum(int i){ T r=0; for(++i;i>0;i-=i&-i) r+=bit[i]; return r; }
    T range_sum(int l,int r){ if(r<l) return 0; return sum(r) - (l?sum(l-1):0); }
};

// Segment Tree (sum)
template<class T>
struct SegTree {
    int n;
    vector<T> st;
    SegTree(int n_=0){ init(n_); }
    void init(int n_){ n=1; while(n<n_) n<<=1; st.assign(2*n,0); }
    void set_point(int p, T v){ st[p+=n]=v; for(p>>=1;p;p>>=1) st[p]=st[2*p]+st[2*p+1]; }
    T query(int l,int r){ // [l,r)
        T res=0;
        for(l+=n, r+=n; l<r; l>>=1, r>>=1){
            if(l&1) res += st[l++];
            if(r&1) res += st[--r];
        }
        return res;
    }
};

// Dijkstra (非负权最短路)
template<class T>
vector<T> dijkstra(const vector<vector<pair<int,T>>>& g, int src){
    const T INF = numeric_limits<T>::max();
    int n = g.size();
    vector<T> dist(n, INF);
    using P = pair<T,int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    dist[src]=0; pq.push({0,src});
    while(!pq.empty()){
        auto [d,u]=pq.top(); pq.pop();
        if(d!=dist[u]) continue;
        for(auto [v,w]: g[u]){
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// Prime sieve
vector<int> sieve_primes(int n){
    vector<int> primes;
    vector<char> is(n+1, true);
    if(n>=0) is[0]=false;
    if(n>=1) is[1]=false;
    for(int i=2;i<=n;i++) if(is[i]){
        primes.push_back(i);
        if((long long)i*i<=n) for(int j=i*i;j<=n;j+=i) is[j]=false;
    }
    return primes;
}

// Combination mod (预处理阶乘)，mod 可替换
struct Comb {
    int n; ll mod;
    vector<ll> fact, ifact;
    Comb(int n=0, ll mod=1): n(n), mod(mod){
        init(n, mod);
    }
    void init(int n_, ll mod_){
        n = n_; mod = mod_;
        fact.assign(n+1,1);
        for(int i=1;i<=n;i++) fact[i] = fact[i-1]*i % mod;
        ifact.assign(n+1,1);
        ifact[n] = modpow(fact[n], mod-2, mod);
        for(int i=n;i>0;i--) ifact[i-1] = ifact[i]*i % mod;
    }
    ll C(int n_, int k_) const {
        if(k_<0 || k_>n_) return 0;
        return fact[n_] * ifact[k_] % mod * ifact[n_-k_] % mod;
    }
};

// 常用输入/输出模板
int main(){
    // 示例框架：读入 t 个测试用例
    int T = 1;
    if(!(cin >> T)) return 0;
    for(int tc=1; tc<=T; ++tc){
        // 在这里处理每个测试用例
        // 例如读取 n 和数组 a
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i=0;i<n;i++) cin >> a[i];

        // 示例：输出数组和
        ll sum = 0;
        for(auto x: a) sum += x;
        cout << sum << '\n';
    }
    return 0;
}