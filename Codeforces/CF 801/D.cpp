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
const ll MOD = 1000000007; // 998244353
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
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

vi gr[MX];
int ans = 0;
int c, root;

// returns if the subtree has a node
bool dfs(int v, int p) {
    int cnt = 0;
    bool ok = 0;
    int no_node = 0;
    bool has_node = 0;
    trav(u, gr[v]) {
        if (u == p) continue;
        cnt++;
        bool ret = dfs(u, v);
        has_node |= ret;
        if (!ret) no_node++;
    }
    if (v == root) c = no_node;
    dbg(v, cnt, has_node, no_node);
    ans += max(no_node-1, 0);
    return (has_node | (no_node > 1));
    
}

pi dfs1(int v, int p) {
    int cnt = 0;
    int x;
    trav(u, gr[v]) {
        if (u == p) continue;
        cnt++;
        x = u;
    }
    if (cnt == 0) return {-1, -1};
    else if (cnt == 1) return dfs1(x, v);
    else return {v, p};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        if (n == 1) {
            cout << 0 << nl;
            continue;
        }
        // if it is line, answer is 1
        F0R(i, n+1) gr[i].clear();
        F0R(i, n-1) {
            int u, v; cin >> u >> v;
            gr[u].pb(v);
            gr[v].pb(u);
        }
        root = -1;
        FOR(i, 1, n) {
            if (sz(gr[i]) == 1) root = i;
        }
        ans = 0;
        c = -1;
        pi ret = dfs1(root, 0);
        // dbg(root, ret.f, ret.s);
        root = ret.f;
        if (ret.f == -1) ans = 1;
        else dfs(ret.f, ret.s);
        if (c > 0) ans++;
        cout << ans << nl;
    }
    return 0;
}
