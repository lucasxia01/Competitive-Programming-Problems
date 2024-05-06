#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define F0R(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define FORd(i,a,b) for (int i = (b); i >= (a); i--)
#define trav(a, x) for (auto& a : x)
#define rep(i, a, b) for(int i = a; i < (b); ++i)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 998244353;
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(...) dbg_out(__VA_ARGS__);
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){
	c << "(" << v.fi << "," <<v.se <<")"; return c;
}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){
	out << "{ ";
	trav(x,c) out<<x<<" ";
	out<<"}"; return out;
}
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e5+5;

const int CUTOFF = 1200;
int n, k;
bool SMALLMODE;
vi gr[MX];
map<int, int> dp[MX];
int smalldp[MX][CUTOFF+5];
int subtreeSize[MX];
int TMP[CUTOFF+5];

void dfs(int v, int p) {
    dp[v][1] = 1;
    map<int, int> tmp;
    trav(u, gr[v]) {
        if (u == p) continue;
        // poly multiply with children
        // traverse up to the size of the subtree
        dfs(u, v);
        tmp.clear();
        trav(a, dp[u]) {
            trav(b, dp[v]) {
                if (a.f+b.f > k+1) continue;
                tmp[a.f+b.f] = (1LL*tmp[a.f+b.f]+1LL*a.s*b.s)%MOD;
            }
        }
        dp[v] = tmp;
    }
    // k and k+1 can become 0;
    if (dp[v].count(k)) dp[v][0] = (dp[v][0]+dp[v][k])%MOD;
    if (dp[v].count(k+1)) dp[v][0] = (dp[v][0]+dp[v][k+1])%MOD;
    // trav(a, dp[v]) {
    //     dbg(v, p, a.f, a.s);
    // }
}

void smalldfs(int v, int p) {
    smalldp[v][1] = 1;
    subtreeSize[v] = 1;
    trav(u, gr[v]) {
        if (u == p) continue;
        smalldfs(u, v);
        // poly multiply with children
        // traverse up to the size of the subtree
        int oldSubtreeSize = subtreeSize[v];
        subtreeSize[v] += subtreeSize[u];
        subtreeSize[v] = min(subtreeSize[v], k+1);
        F0R(i, subtreeSize[v]+1) TMP[i] = 0;
        F0R(j, subtreeSize[u]+1) {
            F0R(i, oldSubtreeSize+1) {
                if (i+j > k+1) continue;
                TMP[i+j] = (1LL*TMP[i+j]+1LL*smalldp[u][j]*smalldp[v][i])%MOD;
            }
        }
        
        F0R(i, subtreeSize[v]+1) smalldp[v][i] = TMP[i];
    }
    // k and k+1 can become 0;
    if (k <= subtreeSize[v]) smalldp[v][0] = (smalldp[v][0]+smalldp[v][k])%MOD;
    if (k+1 <= subtreeSize[v]) smalldp[v][0] = (smalldp[v][0]+smalldp[v][k+1])%MOD;
    // F0R(i, subtreeSize[v]+1) {
    //     dbg(v, p, i, smalldp[v][i]);
    // }
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        cin >> n >> k;
        F0R(i, n+1) {
            gr[i].clear();
            F0R(j, CUTOFF+5) smalldp[i][j] = 0;
            subtreeSize[i] = 0;
            dp[i].clear();
        }
        // O(nk) naive, so just run it up to 400
        F0R(i, n-1) {
            int a, b; cin >> a >> b;
            gr[a].pb(b);
            gr[b].pb(a);
        }
        SMALLMODE = (k < CUTOFF);
        
        // wrap around k+1 if we are in small mode
        // root at 1 and dp it up lets go
        if (SMALLMODE) smalldfs(1, 0);
        else dfs(1, 0);
        // see how many 0s there are
        cout << (SMALLMODE?smalldp[1][0]:dp[1][0]) << nl;
    }
    return 0;
}
