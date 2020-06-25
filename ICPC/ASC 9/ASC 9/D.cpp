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
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 101;

vi gr[MX];
int vis[MX];
vi order;
void dfs1(int v) {
    vis[v] = 1;
    trav(u, gr[v]) {
        if (vis[u]) continue;
        dfs1(u);
    }
    order.pb(v);
}
int out, in, mark = 0, comp = 0;
void dfs2(int v) {
    vis[v] = mark;
    comp++;
    trav(u, gr[v]) {
        if (vis[u]) continue;
        dfs2(u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("police.in", "r", stdin);
//    freopen("police.out", "w", stdout);
    int n, m, k; cin >> n >> m >> k;
    int u, v;
    F0R(i, m) {
        cin >> u >> v;
        gr[u].pb(v);
    }
    FOR(i, 1, n) if (!vis[i]) dfs1(i);
    reverse(order.begin(), order.end());
    memset(vis, 0, sizeof vis);
    vi policeComps;
    trav(a, order) {
        if (!vis[a]) {
            ++mark;
            comp = 0; in = 0; out = 0;
            dfs2(a);
            if (!in || !out) policeComps.pb(comp);
        }
    }
    int SZ = sz(policeComps);
    __int128 dp[SZ+1][k+1]; F0R(i, SZ+1) F0R(j, k+1) dp[i][j] = 0;
    dp[0][0] = 1;
    F0R(i, SZ) {
        F0R(j, k) {
            FOR(l, 1, policeComps[i]) {
                if (j+l > k) break;
                dp[i+1][j+l] += dp[i][j];
            }
        }
    }
    return 0;
}
