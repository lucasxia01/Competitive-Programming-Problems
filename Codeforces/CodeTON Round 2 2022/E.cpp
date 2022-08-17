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

const int MX = 3e5+5;

int n; // number of vertices
vi adj[1005]; // adjacency list of graph
vector<bool> visited;
vector<int> ans;

void dfs(int v) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u])
            dfs(u);
    }
    ans.push_back(v);
}

void topological_sort() {
    visited.assign(n+1, false);
    ans.clear();
    for (int i = 1; i <= n; ++i) {
        if (!visited[i])
            dfs(i);
    }
    reverse(ans.begin(), ans.end());
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int m; cin >> n >> m;
        int a[n]; F0R(i, n) cin >> a[i];
        FOR(i, 1, n) {
            adj[i].clear();
            adj[i].shrink_to_fit();
        }
        F0R(i, m) {
            int x, y; cin >> x >> y;
            adj[x].pb(y);
        }
        topological_sort();
        // trav(aa, ans) cerr << aa << " "; cerr << nl;
        // new ordering
        vpi T[n+1];
        FOR(i, 1, n) if (a[i-1] > 0) T[i].pb({0, a[i-1]});
        int ANS = 0;
        trav(v, ans) {
            sort(all(T[v]));
            // merge all the segments together maybe
            vpi temp;
            pi cur = {-1, -1};
            trav(p, T[v]) {
                // try to merge top two things
                if (cur.f == -1) cur = p;
                else {
                    if (cur.f+cur.s >= p.f) {
                        cur.s = (cur.s+p.s);
                        if (cur.s > 2*MOD) cur.s = (cur.s%MOD) + MOD;
                    } else {
                        temp.pb(cur);
                        cur = p;
                    }
                }
            }
            if (cur.f == -1) continue;
            if (sz(adj[v]) == 0) {
                ANS = (cur.f+cur.s)%MOD;
            }
            temp.pb(cur);
            trav(u, adj[v]) {
                trav(tt, temp) {
                    T[u].pb({tt.f+1, tt.s});
                }
            }
        }
        cout << ANS%MOD << nl;
    }
    return 0;
}
