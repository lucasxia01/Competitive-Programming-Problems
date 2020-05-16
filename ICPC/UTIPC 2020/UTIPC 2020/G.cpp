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

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

const int MX = 105;

int cost[MX][2];
int vis[MX];
ll gr[MX][MX];
int n;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    int c;
    F0R(i, n) {
        cin >> c >> cost[i][0] >> cost[i][1];
        cost[i][0] -= c;
        cost[i][1] -= c;
    }
    int u, v;
    
    int b; cin >> b;
    F0R(i, b) {
        cin >> u >> v >> c;
        gr[u][v] += c;
        gr[v][u] += c;
    }
    F0R(i, n) F0R(j, n) if (gr[i][j] == 0) gr[i][j] = INF;
    F0R(i, n) {
        if (!vis[i]) {
            vis[i] = 1;
            ll ans = dfs(i);
            vis[i] = 2;
            if (ckmin(ans, dfs(i))) vis[i] = 2;
            else vis[i] = 1;
        }
    }
    return 0;
}
