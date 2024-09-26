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

const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 998244353;
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

const int MX = 2.5e5 + 5;
const int LOGMX = 20;
int ti[MX], to[MX];
int par[MX][LOGMX];
vi edges[MX];
int l[MX];
int t = 0;

/*
******** SET N OTHERWISE THIS WON'T WORK *******
 */
int n;
/*
 LCA - finds lowest common ancestor of two nodes in a rooted tree
 * O(nlogn) preprocessing, O(logn) query time
 * Preprocessing is a DFS that finds time in and out of each node, as well as level and direct parent; then, parents with orders of powers of 2 are calculated in a sparse table
 * LCA query is checking if one is a parent of the other and binary searching through binary lifting, searching for highest node that is not an ancestor; returning the parent gives the LCA
 * Tested on NAPC Day -2 F: Fruit Trees on 3/22/2020
    https://codeforces.com/group/ZFgXbZSjvp/contest/272908/problem/F
    https://codeforces.com/gym/102201/problem/F
 */
void dfs(int s, int p, int level) {
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
    dfs(1, 0, 0);
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int q, u, v;
    cin >> n >> q;
    F0R(i, n-1) {
        cin >> u >> v;
        edges[u].pb(v);
        edges[v].pb(u);
    }
    preprocess();
    
    F0R(i, q) {
        cin >> u >> v;
        printf("%d %d %d\n", u, v, lca(u, v));
    }
    return 0;
}
