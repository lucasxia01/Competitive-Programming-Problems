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
const ll MOD = 1000000007LL; // 998244353
const ll MOD2 = 1000000009LL;
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

const int MX = 6e5+5;

struct DSU {
    vi par, SZ, c;
    DSU(int n) {
        par.resize(n+1); SZ.resize(n+1); c.resize(n+1);
        F0R(i, n+1) {
            par[i] = i;
            SZ[i] = 1;
            c[i] = i;
        }
    }

    int find(int i) {
        return (par[i] == i?i:par[i]=find(par[i]));
    }
    void paint(int a, int b) { // paint a to b
        if (c[a]) c[b] = merge(c[a], c[b]);
        c[a] = 0;
    }
    int merge(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return a;
        if (SZ[a] < SZ[b]) swap(a, b);
        SZ[a] += SZ[b];
        par[b] = a;
        return a;
    }
};

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vpi v(m);
    F0R(i, m) cin >> v[i].f >> v[i].s;
    int lo = 0, hi = m;
    DSU d(n);
    DSU cur = d;
    bool win = 1;
    for (int i = 0; i < n; i += k) {
        int r = cur.find(i+1);
        bool ok = 1;
        F0R(j, min(k, n-i)) {
            if (r != cur.find(i+1+j)) ok = 0;
        }
        if (!ok) win = 0;
    }
    if (win) {
        cout << 0 << nl;
        return;
    }
    while (lo < hi) {
        int mid = (lo+hi)/2;
        cur = d;
        // dbg(lo, hi, mid);
        FOR(i, lo, mid) {
            cur.paint(v[i].f, v[i].s);
        }
        // FOR(i, 1, n) cout << cur.find(i) << " "; cout << nl;
        win = 1;
        for (int i = 0; i < n; i += k) {
            int r = cur.find(i+1);
            bool ok = 1;
            F0R(j, min(k, n-i)) {
                if (r != cur.find(i+1+j)) ok = 0;
            }
            if (!ok) win = 0;
        }
        if (win) hi = mid;
        else {
            lo = mid+1;
            d = cur;
        }
    }
    if (lo == m) lo = -2;
    cout << lo+1 << nl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    FOR(i, 1, t) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
