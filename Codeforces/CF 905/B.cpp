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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, T; cin >> n >> T;
    vpi a[T];
    vpi edges[n+1];
    F0R(i, T) {
        int m; cin >> m;
        F0R(j, m) {
            int u, v; cin >> u >> v;
            edges[u].pb({v, i});
            edges[v].pb({u, i});
        }
    }
    // we are at city 1, activate everything in 1
    trav(e, edges[1]) {
        a[e.s].pb({1, e.f});
    }
    bool vis[n+1]; F0R(i, n+1) vis[i] = 0;
    vis[1] = 1;
    int k; cin >> k;
    bool done = 0;
    F0R(i, k) {
        int x; cin >> x; x--;
        dbg("x", x);
        // process the queue in x
        vpi tmp;
        trav(e, a[x]) {
            dbg(e.f, e.s);
            dbg(e.f, e.s);
            dbg(e.f, e.s);


            if (!vis[e.s]) {
                vis[e.s] = 1;
                if (e.s == n) {
                    cout << i+1 << nl;
                    done = 1;
                    break;
                }
                dbg("e.s", e.s);
                trav(g, edges[e.s]) {
                    dbg(g.s, e.s);
                    dbg(e.s);
                    dbg(g.f);
                    if (g.s != x) a[g.s].pb({e.s, g.f});
                    else tmp.pb({e.s, g.f});
                }
            }
        }
        a[x].clear();
        trav(tt, tmp) a[x].pb(tt);
        
        if (done) break;
    }
    if (!done) cout << -1 << nl;
    return 0;
}
