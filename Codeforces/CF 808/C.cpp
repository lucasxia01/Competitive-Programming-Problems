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

const int MX = 1e5+5;

vpi gr[MX];
vi g[MX];
int nxt[MX];
int prev[MX];

int parent[MX], sz[MX];

void make_set(int v) {
    parent[v] = v;
    sz[v] = 1;
}
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}
bool union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b])
            swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
    return false;
}
int n;
int l = 20;
int timer;
vector<int> tin, tout, d;
vector<vector<int>> up;
vi adj[MX];

void dfs(int v, int p, int depth)
{
    tin[v] = ++timer;
    d[v] = depth;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v, depth+1);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n+1);
    tout.resize(n+1);
    d.resize(n+1);
    timer = 0;
    up.assign(n+1, vector<int>(l + 1));
    dfs(root, root, 0);
}

int anc(int v, int dist) {
    F0R(i, l+1) {
        if (dist&(1<<i)) v = up[v][i];
    }
    return v;
}

int total;
int val[MX];
bool ans[MX];

void ans_dfs(int v, int p, int sum) {
    sum += val[v];
    dbg("ANS_DFS", v, sum);
    trav(u, adj[v]) {
        if (u == p) continue;
        ans_dfs(u, v, sum);
    }
    ans[v] = (sum == total);
}

vpi e;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int m; cin >> n >> m;
    F0R(i, m) {
        int a, b; cin >> a >> b;
        e.pb({a, b});
        gr[a].pb({b, i});
        gr[b].pb({a, i});
    }
    FOR(i, 1, n) {
        int temp = m+1;
        trav(u, gr[i]) {
            if (ckmin(temp, u.s)) nxt[i] = u.f;
        }
    }
    FOR(i, 1, n) make_set(i);
    // kruskal's to find relevant edges (unique MST)
    bool used[m];
    F0R(i, m) used[i] = union_sets(e[i].f, e[i].s);
    F0R(i, m) if (used[i]) {
        adj[e[i].f].pb(e[i].s);
        adj[e[i].s].pb(e[i].f);
    }
    preprocess(1);
    F0R(i, m) if (!used[i]) {
        total++;
        int a = e[i].f, b = e[i].s;
        int x = lca(a, b);
        dbg(a, b, x);
        if (x == a) {
            val[b]++;
            val[anc(b, d[b]-d[a]-1)]--;
            total--;
        } else if (x == b) {
            val[a]++;
            val[anc(a, d[a]-d[b]-1)]--;
            total--;
        } else {
            val[a]++;
            val[b]++;
        }
    }
    ans_dfs(1, 0, 0);
    FOR(i, 1, n) cout << ans[i]; cout << nl;
    return 0;
}
