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
const ll INF = (1LL<<55) + 123;
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

const int MX = 5e5+5;

ll a[MX];
vi gr[MX];
ll ans = 0;

// returns the max value from this subtree, using at least something
int dfs(int v, int p) {
    vi ch;
    trav(u, gr[v]) { // at least 1 child
        if (u == p) continue;
        int ret = dfs(u, v);
        ch.pb(ret);
    }
    sort(all(ch));
    reverse(all(ch));
    int ret = -INF;
    if (sz(ch) == 0) {
        ckmax(ans, a[v]);
        return a[v];
    } else {
        // case 1: forget above and assume v is the root
        // 1a: keep v, only possible if num of ch is not 2
        // to keep v, we want 0 children, 1 child, or 3+ children
        ckmax(ans, a[v]);
        ckmax(ans, a[v]+ch[0]);
        if (sz(ch) >= 3) {
            int sum3 = 0;
            F0R(i, 3) sum3 += ch[i];
            FOR(i, 3, sz(ch)-1) if (ch[i] > 0) sum3 += ch[i];
            ckmax(ans, a[v]+sum3);
        }
        // remove v: keep two children
        if (sz(ch) >= 2) ckmax(ans, ch[0]+ch[1]);
        // case 2: assume the above is used
        // 2a: keep v, means we cannot choose only 1 child
        ckmax(ret, a[v]);
        if (sz(ch) >= 2) {
            int sum2 = 0;
            F0R(i, 2) sum2 += ch[i];
            FOR(i, 2, sz(ch)-1) if (ch[i] > 0) sum2 += ch[i];
            ckmax(ret, a[v]+sum2);
        }
        // 2b: remove v, means we keep exactly 1 child
        if (sz(ch) >= 1) ckmax(ret, ch[0]);
        dbg(v, ret);
        return ret;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        int n; cin >> n;
        F0R(i, n) cin >> a[i+1];
        FOR(i, 1, n) gr[i].clear();
        ans = 0;
        F0R(i, n-1) {
            int x, y; cin >> x >> y;
            gr[x].pb(y);
            gr[y].pb(x);
        }
        dfs(1, 0);
        cout << ans << nl;
    }
    return 0;
}
