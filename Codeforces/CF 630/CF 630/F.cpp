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
vi edges[MX];
int n;
ll dp[MX][3];

void dfs(int u, int p) {
    trav(v, edges[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    bool leaf = false;
    if (sz(edges[u]) == 1 && edges[u][0] == p) leaf = true;
    if (leaf) {
        dp[u][0] = 1;
        dp[u][1] = 1;
        return;
    }
    dp[u][0] = 1;
    dp[u][1] = 1;
    trav(v, edges[u]) {
        if (v != p) {
            dp[u][0] = (dp[u][0] * (2*dp[v][0] + dp[v][1]))%MOD;
            dp[u][1] = (dp[u][1] * 2*dp[v][0])%MOD;
        }
    }
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
    cout << (dp[1][0] + dp[1][1])%MOD << endl;
    
    return 0;
}
