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

int par[MX], val[MX];
vi s[MX];
int n, m, h; 

int find(int p) {
    return par[p];
}

int d(int a, int b) {
    return val[b] - val[a];
}

int mod(int x) {
    return (x%h + h)%h;
}

bool merge(int a, int b, int v) {
    if (par[a] == par[b]) {
        dbg("merged", a, b);
        dbg(a, b, d(a, b), v);
        return (mod(d(a, b)) == mod(v));
    } else {
        // small to large
        dbg("not merged", a, b, par[a], par[b]);
        if (sz(s[par[a]]) < sz(s[par[b]])) swap(a, b);
        int old = par[b], oldval = val[b];
        trav(ss, s[old]) {
            val[ss] = val[par[a]] + d(par[a], a) + val[ss] - oldval;
            if (a < n) val[ss] += v;
            else val[ss] -= v;
            dbg(a, b, par[a], par[b], ss, val[ss]);
            par[ss] = par[a];
            s[par[a]].pb(ss);
        }
        s[old].clear();
        return 1;
    }
}


void reset() {
    F0R(i, n+m) {
        par[i] = i;
        s[i].clear(); s[i].pb(i);
        val[i] = 0;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m >> h;
        reset();
        int g[n][m]; F0R(i, n) F0R(j, m) cin >> g[i][j];
        bool ok = 1;
        F0R(i, n) {
            F0R(j, m) {
                dbg(i, j, g[i][j]);
                if (g[i][j] != -1) ok &= merge(i, n+j, g[i][j]);
            }
        }
        int cnt = 0;
        F0R(i, n+m) cnt += (par[i] == i);
        ll ans = 1;
        F0R(i, cnt-1) ans = (ans*h)%MOD;
        cout << (ok?ans:0) << nl;
    }
    return 0;
}
