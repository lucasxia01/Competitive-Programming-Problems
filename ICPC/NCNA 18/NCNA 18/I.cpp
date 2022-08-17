#include <iostream>
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

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, k1, k2;
    cin >> n >> m >> k1 >> k2;
    int dp[n+1][k1+1][k2+1][2];
    F0R(i, n+1) F0R(j, k1+1) F0R(k, k2+1) F0R(l, 2) dp[i][j][k][l] = INF;
    int time[n+1][n+1];
    int color[n+1][n+1];
    int bestWhite[n+1][n+1];
    F0R(i, n+1) F0R(j, n+1) time[i][j] = -1;
    F0R(i, n+1) F0R(j, n+1) color[i][j] = -1;
    
    vector<int> e[n+1];
    int u, v, t, c, s;
    F0R(i, m) {
        cin >> u >> v >> t >> c;
        e[u].pb(v);
        e[v].pb(u);
        time[u][v] = time[v][u] = t;
        color[u][v] = color[v][u] = c;
    }
    cin >> s >> t;
    
    
    
    return 0;
}
