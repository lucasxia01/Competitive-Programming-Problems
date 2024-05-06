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

vi gr[MX];
int mark[MX];

bool dfs(int v, int m) {
    mark[v] = m;
    trav(u, gr[v]) {
        if (mark[u] != -1) {
            if (mark[u] != 1-m) return 0;
            else continue;
        }
        if (!dfs(u, 1-m)) return 0;
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<array<int, 3>> v;
    F0R(i, m) {
        int a, b, c; cin >> a >> b >> c; a--; b--;
        v.pb({a, b, c});
    }
    int lo = 1, hi = 2e9+1;
    vi e[n];
    trav(a, v) {
        e[a[0]].pb(a[2]);
        e[a[1]].pb(a[2]);
    }
    dbg(n);
    F0R(i, n) {
        sort(all(e[i]));
        if (sz(e[i]) >= 2) {
            ckmin(hi, e[i][0]+e[i][1]);
        }
    }
    set<int> vals; vals.insert(hi);
    // push all the small vals <= hi
    trav(a, v) {
        if (a[2] <= hi) vals.insert(a[2]);
    }

    dbg(hi);
    // binary search on x
    lo = 0, hi = sz(vals);
    vi c; trav(vv, vals) c.pb(vv);
    while (lo < hi) {
        int idx = (lo+hi)/2;
        int mid = c[idx];
        // filter for edges less than mid
        F0R(i, n) gr[i].clear();
        F0R(i, n) mark[i] = -1;
        trav(a, v) {
            if (a[2] < mid) {
                gr[a[0]].pb(a[1]);
                gr[a[1]].pb(a[0]);
            }
        }
        bool ok = 1;
        if (ok) { // now do a dfs or bfs or whatever
            F0R(i, n) {
                if (mark[i] == -1) {
                    if (!dfs(i, 0)) {
                        ok = 0;
                        break;
                    }
                }
            }
        }
        if (ok) lo = idx+1;
        else hi = idx;
    }
    cout << c[lo-1] << nl;
    return 0;
}
