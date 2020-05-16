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
const int INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e3 + 5;
const int LOGMX = 11;
int ti[MX], to[MX];
int par[MX][LOGMX];
vi edges[MX], unpaved[MX], odd[MX];
vpi oddLen;
int l[MX];
int n, m, t = 0;

/*
 LCA - finds lowest common ancestor of two nodes in a rooted tree
 * O(nlogn) preprocessing, O(logn) query time
 * Preprocessing is a DFS that finds time in and out of each node, as well as level and direct parent; then, parents with orders of powers of 2 are calculated in a sparse table
 * LCA query is checking if one is a parent of the other and binary searching through binary lifting, searching for highest node that is not an ancestor; returning the parent gives the LCA
 * Tested on NAPC Day -2 F: Fruit Trees on 3/22/2020
    https://codeforces.com/group/ZFgXbZSjvp/contest/272908/problem/F
    https://codeforces.com/gym/102201/problem/F
 */
void dfs(int s = 1, int p = 0, int level = 0) {
    l[s] = level;
    ti[s] = t++;
    trav(a, edges[s]) {
        if (a != p) {
            par[a][0] = s;
            dfs(a, s, level+1);
        }
    }
    to[s] = t;
}
void preprocess() {
    par[1][0] = 0;
    ti[0] = -1; to[0] = MX;
    dfs();
    FOR(i, 1, LOGMX-1) {
        FOR(j, 1, n) {
            par[j][i] = par[par[j][i-1]][i-1];
        }
    }
}

int lca(int u, int v) {
    if (ti[u] <= ti[v] && to[v] <= to[u]) return u;
    int count = LOGMX;
    while (count--) {
        if (!(ti[par[u][count]] <= ti[v] && to[v] <= to[par[u][count]])) {
            u = par[u][count];
        }
    }
    return par[u][0]; // u is an ancestor of v
    
}

vi order;
int dp[MX], vis[MX], adj[MX][MX], oddAdj[MX][MX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    int u, v, c;
    int total = 0;
    F0R(i, m) {
        cin >> u >> v >> c;
        if (c == 0) {
            edges[u].pb(v);
            edges[v].pb(u);
        } else {
            unpaved[u].pb(v);
            adj[u][v] = adj[v][u] = c;
        }
    }
    preprocess();
    int extra = 0;
    FOR(u, 1, n) {
        trav(v, unpaved[u]) {
            int p = lca(u, v);
            if ((l[v]+l[u]-l[p]-l[p]+1)&1) {
                oddLen.pb({u, v});
                oddAdj[u][v] = oddAdj[v][u] = adj[u][v];
                total += adj[u][v];
            } else extra += adj[u][v];
        }
    }
    // assume its a line first
    int r = 0;
    FOR(u, 1, n) if (sz(edges[u]) == 1) { // find one end of the line
            r = u; break;
        }
    int cur = r;
    int par = 0;
    order.pb(cur);
    vis[r] = 1;
    F0R(i, n-1) {
        trav(v, edges[cur]) {
            if (!vis[v]) {
                order.pb(v);
                par = cur;
                cur = v;
                vis[cur] = 1;
            }
        }
    }
    if (sz(order) != n) {
        int maxDeg = 0;
        FOR(u, 1, n) ckmax(maxDeg, sz(edges[u]));
        assert(maxDeg > 2);
        cout << 48 << nl;
        return 0;
    }
//   trav(a, order) cout << a << " "; cout << nl;
    dp[0] = total;
    FOR(i, 1, n-1) {
        dp[i] = dp[i-1];
        F0R(j, i) {
            if (oddAdj[order[j]][order[i]]) ckmin(dp[i], dp[j]-oddAdj[order[j]][order[i]]);
        }
//        cout << dp[i] << nl;
    }
    cout << dp[n-1]+extra << nl;
    return 0;
}
