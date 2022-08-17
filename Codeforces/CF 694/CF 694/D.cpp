#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <chrono>
#include <cassert>
#include <climits>

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
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;
vi gr[MX];
int vis[MX];
void dfs(int v) {
    if (vis[v]) return;
    vis[v] = 1;
    trav(u, gr[v]) dfs(u);
}
vi ans;
void bfs() {
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        // dbg(v, vis[v]);
        if (vis[v] >= 3) continue;
        trav(u, gr[v]) {
            if (vis[u] == 3) continue;
            ckmax(vis[u], 3 - vis[v]);
            q.push(u);
        }
        if (vis[v] == 1) {
            ans.pb(v);
            vis[v] = 3;
        }
        if (vis[v] == 2) {
            vis[v] = 4;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        F0R(i, n+1) gr[i].clear();
        F0R(i, n+1) vis[i] = 0;
        F0R(i, m) {
            int u, v; cin >> u >> v;
            gr[u].pb(v);
            gr[v].pb(u);
        }
        ans.clear();
        bfs();
        bool ok = 1;
        FOR(i, 1, n) if (!vis[i]) ok = 0;
        cout << (ok ? "YES":"NO") << nl;
        if (ok) {
            cout << sz(ans) << nl;
            trav(a, ans) cout << a << " "; cout << nl;
        }
    }
    return 0;
}
