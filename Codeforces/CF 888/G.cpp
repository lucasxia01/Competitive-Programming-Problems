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

const int MX = 3e5+5;

int parent[MX], SZ[MX];
int find_set(int v) {
if (v == parent[v])
    return v;
return parent[v] = find_set(parent[v]);
}
void make_set(int v) {
    parent[v] = v;
    SZ[v] = 1;
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

vi gr[MX];
int n, m;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        int h[n]; F0R(i, n) cin >> h[i];
        vpi a;
        F0R(i, n) a.pb({h[i], i});
        sort(all(a));
        F0R(i, n) gr[i].clear();
        F0R(i, m) {
            int u, v; cin >> u >> v;
            u--; v--;
            if (h[u] < h[v]) swap(u, v);
            gr[u].pb(v);
        }
        int q; cin >> q;
        vector<array<int, 3> > qs(q);
        vpi v;
        F0R(i, q) {
            F0R(j, 3) cin >> qs[i][j];
            qs[i][0]--;
            qs[i][1]--;
            v.pb({qs[i][2]+h[qs[i][0]], i});
        }
        sort(all(v));
        int j = 0;
        a.pb({2e9+5, -1});
        // put them all in buckets
        F0R(i, n) make_set(i);
        bool ans[q];
        F0R(i, n+1) {
            while (j < q && v[j].f < a[i].f) {
                int t = v[j].s;
                if (find_set(qs[t][0]) == find_set(qs[t][1])) ans[t] = 1;
                else ans[t] = 0;
                j++;
            }
            if (i == n) continue;
            int idx = a[i].s;
            trav(p, gr[idx]) {
                dbg(i, idx, p);
                union_sets(idx, p);
            }
        }
        F0R(i, q) cout << (ans[i]?"YES":"NO") << nl;
        cout << nl;

    }
    return 0;
}
