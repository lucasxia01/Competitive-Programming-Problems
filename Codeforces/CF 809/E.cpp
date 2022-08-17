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

const int MX = 2e5+5;

const int LOGQ = 20;

int P[MX], sz[MX];
int n;
int FIND(int v) {
    return (v == P[v]?v:P[v]=FIND(P[v]));
}
bool MERGE(int a) {
    // dbg("MERGE", a);
    int b = FIND(a+1);
    a = FIND(a);
    if (a == b) return 0;
    if (sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    P[b] = a;
    return 1;
}

bool same(pi p) {
    return (FIND(p.f) == FIND(p.s));
}

int par[MX];
vi v[MX];

int find(int v) {
    if (v < 1 || v > n) return -1;
    return (v == par[v]?v:par[v]=find(par[v]));
}

void merge(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (sz(v[a]) < sz(v[b])) swap(a, b);
    trav(u, v[b]) {
        v[a].pb(u);
        if (find(u-1) == a) {
            MERGE(u-1);
        } 
        if (find(u+1) == a) {
            MERGE(u);
        } 
    }
    par[b] = a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int m, q; cin >> n >> m >> q;
        vpi e;
        F0R(i, m) {
            int u, v; cin >> u >> v;
            e.pb({u, v});
        }
        vpi qw(q);
        F0R(i, q) cin >> qw[i].f >> qw[i].s;
        // pbs
        vi check[m+1];
        pi r[q];
        F0R(i, q) {
            r[i] = {0, m};
        }
        F0R(i, LOGQ) {
            F0R(i, m+1) check[i].clear();
            F0R(j, q) {
                check[(r[j].f+r[j].s)/2].pb(j);
                // dbg(r[j].f, r[j].s);
            }
            // maintain a dsu of size n
            F0R(j, n+1) {
                par[j] = j;
                sz[j] = 1;
                P[j] = j;
                v[j].clear(); v[j].pb(j);
            }

            F0R(j, m) {
                trav(c, check[j]) {
                    // dbg(j, c, same(qw[c]));
                    if (same(qw[c])) r[c] = {r[c].f, j};
                    else r[c] = {j+1, r[c].s};
                }
                // add in edge j
                merge(e[j].f, e[j].s);
            }
        }
        F0R(i, q) cout << r[i].f << " "; cout << nl;
    }
    return 0;
}
