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

const int MX = 2e5+5;

int par[MX];
priority_queue<pi, vector<pi>, greater<pi>> pq[MX]; // min pq
int eaten[MX];

int find(int x){
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
}

void merge(int x, int y) { // move y into x
    x = find(x); y = find(y);
    if (x == y) return;
    while (!pq[y].empty()) {
        auto a = pq[y].top(); pq[y].pop();
        pq[x].push(a);
    }
    par[y] = x;
    eaten[x] += eaten[y];
    eaten[y] = 0;
}

vi gr[MX];
int a[MX];
bool vis[MX];

int n, m;

bool bfs(int v) {
    pq[v].push({0,v});
    while (!pq[v].empty()) {
        auto [d,u] = pq[v].top();
        if (d > eaten[v]) return false;
        pq[v].pop();
        if (vis[u] && find(u) == find(v)) continue;
        else if (vis[u]) {
            merge(v, u);
        } else {
            vis[u] = 1;
            eaten[v]++;
            merge(v, u);
            trav(uu, gr[u]) {
                pq[v].push({a[uu],uu});
            }
        }
    }
    return eaten[v] == n;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        F0R(i, n) { // reset
            par[i] = i;
            while (!pq[i].empty()) pq[i].pop();
            eaten[i] = 0;
            gr[i].clear();
            vis[i] = 0;
        }
        F0R(i, n) cin >> a[i];
        F0R(i, m) {
            int u, v; cin >> u >> v; u--; v--;
            gr[u].pb(v);
            gr[v].pb(u);
        }
        bool ok = 0;
        F0R(i, n) {
            if (vis[i] || a[i]) continue;
            if (bfs(i)) ok = 1;
        }
        cout << (ok ? "YES" : "NO") << nl;
    }
    return 0;
}
