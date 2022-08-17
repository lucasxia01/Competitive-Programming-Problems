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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 2.5e5 + 5;
const int LOGMX = 18;
int ti[MX], to[MX];
int par[MX][LOGMX];
vi edges[MX];
int l[MX];
int n, t = 0;

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

vector<pair<int, pi> > qs[MX];
int freq[MX], c[MX];
const int N_ITER = 15;
vi ans[MX];

void dfs2(int s = 1, int p = 0) { // calculates frequencies of colors and answers queries about them for each node
    freq[c[s]]++;
    trav(a, qs[s]) {
        if (a.s.s >= N_ITER) ans[a.s.f][a.s.s-N_ITER] += freq[a.f];
        else ans[a.s.f][a.s.s] -= freq[a.f];
    }
    trav(a, edges[s]) {
        if (a != p) {
            par[a][0] = s;
            dfs2(a, s);
        }
    }
    freq[c[s]]--;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int q, u, v;
    cin >> n >> q;
    int counts[n+1];
    memset(counts, 0, 4*n+4);
    F0R(i, n) {
        cin >> c[i+1];
        counts[c[i+1]]++;
    }
    F0R(i, n-1) {
        cin >> u >> v;
        edges[u].pb(v);
        edges[v].pb(u);
    }
    preprocess(); // preprocess LCA
    int pathLen[q];
    vi pickedNode[q];
    int marked[n+1];
    memset(marked, 0, 4*n+4);
    F0R(i, q) {
        cin >> u >> v;
        int LCA = lca(u, v);
        pathLen[i] = l[u]+l[v]-2*l[LCA]+1;
        int count = 0;
        F0R(j, N_ITER) {
            int num = rng()%pathLen[i]; // pick random number on path
            int node = u;
            if (num >= l[u]-l[LCA]) {
                node = v;
                num = pathLen[i]-1-num;
            }
            int exp = 0;
            while (num) { // this is to get the correct node
                if (num&1)node = par[node][exp];
                num>>=1;
                exp++;
            }
            if (marked[c[node]] || 2*counts[c[node]] <= pathLen[i]) continue; // optimizations
            marked[c[node]] = 1;
            // add in queries for this color on this path, freq[u]-freq[LCA]+freq[v]-freq[par(LCA)] is the whole path
            qs[par[LCA][0]].pb(mp(c[node], mp(i, count)));
            qs[LCA].pb(mp(c[node], mp(i, count)));
            qs[u].pb(mp(c[node], mp(i, count+N_ITER)));
            qs[v].pb(mp(c[node], mp(i, count+N_ITER)));
            ans[i].pb(0);
            pickedNode[i].pb(node);
            count++;
        }
        F0R(j, pickedNode[i].size()) marked[c[pickedNode[i][j]]] = 0;
    }
    dfs2(); // answers the queries that were set up
    F0R(i, q) {
        bool ok = false;
        int j;
        for (j = 0; j < ans[i].size(); j++) if (2*ans[i][j] > pathLen[i]) {
            ok = true;
            break;
        }
        if (ok) cout << c[pickedNode[i][j]] << endl;
        else cout << -1 << endl;
    }
    return 0;
}
