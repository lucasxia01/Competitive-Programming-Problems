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

const int MX = 1e5+5;

int par[MX];
set<int> st[MX];

int find(int x) {
    if (par[x] == x) return x;
    return par[x] = find(par[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (sz(st[x]) < sz(st[y])) swap(x, y);
    par[y] = x;
    st[x].insert(st[y].begin(), st[y].end());
}

vi gr[MX];
vector<array<int, 3> > qs[MX];
int idx[MX];
bool ans[MX];

void dfs(int v, int p) {
    st[v].insert(idx[v]);
    trav(u, gr[v]) {
        if (u == p) continue;
        dfs(u, v);
        merge(v, u);
    }
    // now answer queries
    int cur = find(v);
    // dbg("at node", v, sz(st[cur]));
    // trav(uu, st[cur]) {
    //     cerr << uu << ' ';
    // } cerr << nl;
    trav(q, qs[v]) {
        int l = q[0], r = q[1], id = q[2];
        dbg("query", l, r, id, st[cur].lower_bound(l) != st[cur].lower_bound(r));
        if (st[cur].lower_bound(l) != st[cur].lower_bound(r)) ans[id] = 1;
        else ans[id] = 0;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        int n, q; cin >> n >> q;
        FOR(i, 1, n) {
            gr[i].clear();
            st[i].clear();
            par[i] = i;
            qs[i].clear();
        }
        F0R(i, n-1) {
            int a, b; cin >> a >> b;
            gr[a].pb(b);
            gr[b].pb(a);
        }
        int p[n]; F0R(i, n) cin >> p[i];
        F0R(i, n) idx[p[i]] = i;

        F0R(i, q) {
            int l, r, x; cin >> l >> r >> x;
            l--;
            qs[x].pb({l, r, i});
        }
        dfs(1, 0);
        F0R(i, q) cout << (ans[i] ? "YES" : "NO") << nl;
        cout << nl;
    }
    return 0;
}
