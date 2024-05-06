#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
#define int ll

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
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e5+5;

int parent[MX], SZ[MX];
void make_set(int v) {
    parent[v] = v;
    SZ[v] = 1;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (SZ[a] < SZ[b])
            swap(a, b);
        parent[b] = a;
        SZ[a] += SZ[b];
    }
}

int solve() {
    int n; cin >> n;
    vpi gr[n];
    int a[n]; F0R(i, n) cin >> a[i];
    int b[n]; F0R(i, n) cin >> b[i];
    F0R(i, n) {
        a[i]--; b[i]--;
    }
    // top sort sorta
    bool done[n]; F0R(i, n) done[i] = 0;
    int ans = 1;
    queue<int> q;
    int deg[n]; F0R(i, n) deg[i] = 0;
    bool vis[n]; F0R(i, n) vis[i] = 0;
    F0R(i, n) {
        gr[a[i]].pb({b[i], i});
        gr[b[i]].pb({a[i], i});
        deg[a[i]]++;
        deg[b[i]]++;
    }
    F0R(i, n) {
        if (deg[i] == 1) q.push(i);
    }
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        done[cur] = 1;
        trav(u, gr[cur]) {
            vis[u.s] = 1;
            deg[u.f]--;
            if (deg[u.f] == 1) q.push(u.f);
        }
    }
    // now find degrees of things
    F0R(i, n) deg[i] = 0;
    F0R(i, n) {
        make_set(i);
    }
    F0R(i, n) {
        if (!vis[i]) {
            union_sets(a[i], b[i]);
            deg[a[i]]++;
            deg[b[i]]++;
        }
    }

    bool ok = 1;
    int cnt = 0;
    F0R(i, n) {
        if (!done[i]) {
            if (find_set(i) == i) {
                if (SZ[i] == 1) ans = (ans * n) %MOD;
                else ans = (ans * 2)%MOD;
            }
            if (deg[i] != 2) ok = 0;
        }
    }
    if (!ok) {
        return 0;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cout << solve() << nl;
    }
    return 0;
}
