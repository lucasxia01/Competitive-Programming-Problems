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

vi gr[MX], rgr[MX];
int inCycle[MX];
int vis[MX];
int a[MX];
vi sinks;

void dfs(int v) {
    if (sz(gr[v]) == 0) {
        sinks.pb(v);
        vis[v] = 2;
        return;
    } else if (vis[v] == 1) {
        // found cycle
        int s = gr[v][0];
        vi V; V.pb(v);
        while (s != v) {
            V.pb(s);
            vis[s] = 2;
            s = gr[s][0];
        }
        trav(u, V) inCycle[u] = v+1;
        sinks.pb(v);
        vis[v] = 2;
        return;
    } else if (vis[v] == 2) return;
    vis[v] = 1;
    dfs(gr[v][0]);
    vis[v] = 2;
}

int dp[MX];
map<int, int> m;
int ans = 0;
void dfs2(int v) {
    if (dp[v] != -1) return;
    vi neighbors;
    vi V;
    if (inCycle[v]) {
        int s = gr[v][0];
        if (!m.count(a[v]) || m[a[v]] == 0) ans++;
        m[a[v]]++;
        V.pb(v);
        while (s != v) {
            if (!m.count(a[s]) || m[a[s]] == 0) ans++;
            m[a[s]]++;
            V.pb(s);
            s = gr[s][0];
        }
        trav(u, V) dp[u] = ans;
        trav(u, V) {
            // dbg(v, u);
            trav(w, rgr[u]) {
                if (!inCycle[w]) neighbors.pb(w);
            }
        }
    } else {
        if (!m.count(a[v]) || m[a[v]] == 0) ans++;
        m[a[v]]++;
        neighbors = rgr[v];
    }
    // dbg(v, "neighbors");
    // trav(u, neighbors) cerr << u << " "; cerr << nl;
    dp[v] = ans;
    trav(u, neighbors) {
        dfs2(u);
    }
    if (!inCycle[v]) {
        m[a[v]]--;
        if (m[a[v]] == 0) ans--;
    } else {
        trav(u, V) {
            m[a[u]]--;
            if (m[a[u]] == 0) ans--;
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    F0R(i, n) cin >> a[i];
    // construct the graph and find the cycles
    F0R(i, n) {
        if (i+a[i] >= 0 && i+a[i] < n) {
            gr[i].pb(i+a[i]);
            rgr[i+a[i]].pb(i);
        }
    }
    // find all the cycles
    F0R(i, n) dfs(i);

    F0R(i, n) dp[i] = -1;
    trav(i, sinks) {
        dfs2(i);
        assert(ans == 0);
    }
    ll ans = 0;
    F0R(i, n) {
        // dbg(dp[i]);
        ans+=dp[i];
    }
    cout << ans << nl;
    return 0;
}
