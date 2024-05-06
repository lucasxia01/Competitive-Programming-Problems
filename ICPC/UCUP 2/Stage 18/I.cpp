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
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

int n, m;
vi gr[MX];
vector<vector<int>> adj, adj_rev;
vector<bool> used;
vector<int> order, component;

void dfs1(int v) {
    used[v] = true;

    for (auto u : adj[v])
        if (!used[u])
            dfs1(u);

    order.push_back(v);
}

void dfs2(int v) {
    used[v] = true;
    component.push_back(v);

    for (auto u : adj_rev[v])
        if (!used[u])
            dfs2(u);
}

vi nodes;
bool seen[MX];
void dfs(int v) {
    if (seen[v]) return;
    seen[v] = true;
    nodes.pb(v);
    for (auto u : gr[v])
        dfs(u);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    adj.resize(n+1);
    adj_rev.resize(n+1);
    F0R(i, m) {
        int a, b, c; cin >> a >> b >> c;
        gr[a].push_back(b);
        if (c == 2) {
            adj[a].push_back(b);
        }
    }
    dfs(1);
    trav(u, nodes) {
        dbg(u);
        for (auto v : adj[u]) {
            adj_rev[v].push_back(u);
            dbg(v, u);
        }
    }

    used.assign(n+1, false);

    trav(u, nodes)
        if (!used[u])
            dfs1(u);

    used.assign(n+1, false);
    reverse(order.begin(), order.end());

    vector<int> roots(n+1, 0);
    vector<int> root_nodes;
    vector<vector<int>> adj_scc(n+1);

    for (auto v : order)
        if (!used[v]) {
            dfs2(v);

            int root = component.front();
            for (auto u : component) roots[u] = root;
            root_nodes.push_back(root);
            // cerr << "component " << root << ": ";
            // trav(u, component) cerr << u << " "; cerr << nl;
            
            component.clear();
        }

    bool ok = 0;
    trav(v, nodes)
        for (auto u : adj[v]) {
            int root_v = roots[v],
                root_u = roots[u];

            if (root_u != root_v) {
                dbg("ans", root_v, root_u);
                adj_scc[root_v].push_back(root_u);
                ok = 1;
            }
        }
    cout << (ok?"Yes":"No") << nl;
    return 0;
}
