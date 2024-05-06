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

vi gr[MX];
int par[MX], SZ[MX];

int find (int u) {
    if (par[u] == u) return u;
    return par[u] = find(par[u]);
}

void merge (int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    if (SZ[u] < SZ[v]) swap(u, v);
    par[v] = u;
    SZ[u] += SZ[v];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    int T = t;
    vpi V;
    while (t--) {
        int n, m; cin >> n >> m; // should be k^2 and k^2 + k
        V.pb({n, m});
        vpi edges;
        F0R(i, n) gr[i].clear();
        F0R(i, n) {
            par[i] = i;
            SZ[i] = 1;
        }
        F0R(i, m) {
            int u, v; cin >> u >> v; u--; v--;
            edges.pb({u+1, v+1});
            gr[u].pb(v);
            gr[v].pb(u);
        }
        int k = m-n;
        if (k <= 0 || k >= 1000) {
            cout << "NO" << nl;
            continue;
        }
        if (k*k != n || k*k+k != m) {
            cout << "NO" << nl;
            continue;
        }
        // now verify the k-cycles in the graph
        set<int> s;
        bool ok = 1;
        F0R(i, n) {
            if (sz(gr[i]) == 4) {
                int cnt = 0;
                trav(u, gr[i]) {
                    if (sz(gr[u]) == 4) {
                        merge(u, i);
                        cnt++;
                    }
                }
                if (cnt != 2) ok = 0;
                s.insert(i);
            } else if (sz(gr[i]) != 2) ok = 0;
        }
        dbg(k, *s.begin(), find(*s.begin()), SZ[find(*s.begin())]);
        if (!ok || sz(s) != k || SZ[find(*s.begin())] != k) {
            cout << "NO" << nl;
            continue;
        }
        F0R(i, n) {
            if (sz(gr[i]) == 4) {
                // remove the edges
                vi tmp;
                trav(u, gr[i]) {
                    if (s.find(u) == s.end()) {
                        tmp.pb(u);
                    }
                }
                gr[i] = tmp;
            }
        }
        F0R(i, n) {
            par[i] = i;
            SZ[i] = 1;
        }
        // now check the other cycles for length k
        F0R(i, n) {
            if (sz(gr[i]) != 2) ok = 0;
            trav (u, gr[i]) {
                merge (u, i);
            }
        }
        int cnt = 0;
        F0R(i, n) {
            if (SZ[find(i)] != k) {
                ok = 0;
            }
            if (find(i) == i) {
                cnt++;
            }
        }
        set<int> s2;
        trav(ss, s) {
            s2.insert(find(ss));
        }
        dbg(cnt);
        if (!ok || cnt != k || sz(s2) != k) {
            cout << "NO" << nl;
            continue;
        }
        cout << "YES" << nl;
    }
    return 0;
}
