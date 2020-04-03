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

const int MX = 3e5 + 5;
vi edges[MX];
int n;
ll dp[MX][5];

void dfs(int u, int p) {
    trav(v, edges[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    dp[u][0] = 1; // is not in edge-induced graph, no parent or children edges
    dp[u][1] = 1; // is in edge-induced graph, parent edge exists, and possibly children, not in the independent set
    dp[u][2] = 1; // in graph, with parent edge, in the ind set
    dp[u][3] = 0; // in graph, no parent edge, not in ind set
    dp[u][4] = 0; // in graph, no parent edge, in ind set
    trav(v, edges[u]) {
        if (v != p) {
            dp[u][0] = (dp[u][0] * (dp[v][0] + dp[v][3] + dp[v][4]))%MOD;
            dp[u][1] = (dp[u][1] * (dp[v][0] + dp[v][1] + dp[v][2] + dp[v][3] + dp[v][4]))%MOD;
            dp[u][2] = (dp[u][2] * (dp[v][0] + dp[v][1] + dp[v][3] + dp[v][4]))%MOD;
        }
    }
    dp[u][3] = ((dp[u][1] - dp[u][0])%MOD+MOD)%MOD; // 3 is just 1 without the case where it has no children edges (which is somehow equivalent to 0)
    dp[u][4] = ((dp[u][2] - dp[u][0])%MOD+MOD)%MOD;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int u, v;
    cin >> n;
    F0R(i, n-1) {
        cin >> u >> v;
        edges[u].pb(v);
        edges[v].pb(u);
    }
    dfs(1, 0);
    cout << (dp[1][0] + dp[1][3] + dp[1][4]-1)%MOD << endl;
    
    return 0;
}
