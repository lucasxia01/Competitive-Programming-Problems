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

int n, l;
vector<vector<int>> adj;
vector<int> sums;
vector<int> val;

struct info {
    int up, hi, lo, d1, d2;
};

int timer;
vector<int> tin, tout;
vector<vector<info> > V;

int par(int u) {
    return V[u][0].up;
}

info merge(info a, info other) {
    info ret = a;
    ret.up = other.up;
    // dbg(ret.hi, ret.lo, other.lo, other.hi);
    ckmin(ret.d1, min(other.d1, sums[ret.hi]-sums[other.lo]));
    ckmax(ret.d2, max(other.d2, sums[ret.lo]-sums[other.hi]));
    if (sums[other.hi] < sums[ret.hi]) ret.hi = other.hi;
    if (sums[other.lo] > sums[ret.lo]) ret.lo = other.lo;
    return ret;
}

void dfs(int v, int p)
{
    sums[v] = sums[p] + val[v];
    tin[v] = ++timer;
    V[v][0].up = p;
    V[v][0].hi = V[v][0].lo = v;
    V[v][0].d1 = V[v][0].d2 = 0;
    for (int i = 1; i <= l; ++i) {
        int anc = V[v][i-1].up;
        V[v][i] = merge(V[v][i-1], V[anc][i-1]);
    }

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{   
    if (u == 0) return 1;
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

pi lca(int u, int v) // u -> v
{   
    if (u == v) {
        info R = V[u][0];
        return {min(0, val[u]), max(0, val[u])};
    } else if (is_ancestor(u, v)) {
        int vv = v;
        info R = {v, v, v, 0, 0};

        for (int i = l; i >= 0; --i) {
            if (!is_ancestor(V[vv][i].up, u)) {
                R = merge(R, V[vv][i]);
                vv = V[vv][i].up;
            }
        }
        R = merge(merge(R, V[vv][1]), V[par(vv)][1]);
        int plca = V[vv][1].up;
        return {min(R.d1, sums[R.hi]-sums[plca]), max(R.d2, sums[R.lo]-sums[plca])};
    } else if (is_ancestor(v, u)) {
        int uu = u;
        info L = {u, u, u, 0, 0};
        for (int i = l; i >= 0; --i) {
            if (!is_ancestor(V[uu][i].up, v)) {
                L = merge(L, V[uu][i]);
                uu = V[uu][i].up;
            }
        }
        L = merge(merge(L, V[uu][1]), V[par(uu)][1]);
        int plca = V[uu][1].up;
        return {min(L.d1, sums[L.hi]-sums[plca]), max(L.d2, sums[L.lo]-sums[plca])};
    }
    int uu = u, vv = v;
    info L, R;
    L = {u, u, u, MX, -MX};
    R = {v, v, v, MX, -MX};
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(V[uu][i].up, v)) {
            L = merge(L, V[uu][i]);
            uu = V[uu][i].up;
        }
    }
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(V[vv][i].up, u)) {
            R = merge(R, V[vv][i]);
            vv = V[vv][i].up;
        }
    }
    int lca = V[uu][0].up; // lca
    int plca = V[uu][1].up; // parent of lca
    int lo = 0, hi = 0;
    L = merge(merge(L, V[uu][1]), V[par(uu)][1]); // move up 2 on left
    R = merge(R, V[vv][1]); // move up 1 on right
    dbg(u, v, uu, vv, lca, plca, L.d1, R.d1, L.d2, R.d2);
    dbg(V[uu][1].d1, V[uu][1].d2, V[uu][1].lo, V[uu][1].hi);
    ckmin(lo, min(L.d1, R.d1));
    ckmin(lo, sums[L.hi]+sums[R.hi]-sums[lca]-sums[plca]);
    ckmax(hi, max(L.d2, R.d2));
    ckmax(hi, sums[L.lo]+sums[R.lo]-sums[lca]-sums[plca]);
    return {lo, hi};
}

void preprocess() {
    tin.resize(n+1);
    tout.resize(n+1);
    sums.resize(n+1);
    timer = 0;
    l = ceil(log2(n));
    V.assign(n+1, vector<info>(l + 1));
    dfs(1, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        vpi es;
        vector<array<int, 3> > qs;
        while (n--) {
            char c; cin >> c;
            if (c == '+') {
                int a, b; cin >> a >> b;
                es.pb({a, b});
            } else {
                int a, b, c; cin >> a >> b >> c;
                qs.pb({a, b, c});
            }
        }
        n = sz(es)+1;
        adj.resize(n+1);
        val.resize(n+1);
        val[1] = 1;
        FOR(i, 1, n) adj[i].clear();
        F0R(i, n-1) {
            int u = i+2;
            dbg(es[i].f, u);
            adj[es[i].f].pb(u);
            adj[u].pb(es[i].f);
            val[u] = es[i].s;
        }
        preprocess();
        trav(q, qs) {
            pi ret = lca(q[0], q[1]);
            dbg(q[0], q[1], ret.f, ret.s);
            if (ret.f <= q[2] && q[2] <= ret.s) cout << "YES" << nl;
            else cout << "NO" << nl;
        }
    }
    return 0;
}
