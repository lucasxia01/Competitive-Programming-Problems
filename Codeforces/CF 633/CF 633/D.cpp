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

const int MX = 1e5+5;

vi e[MX];
int dp[MX][2];
int ans = 0;

void dfs(int v=1, int p=0) {
    int SZ = sz(e[v]);
    dp[v][1] += SZ;
    vpi take, skip;
    trav(u, e[v]) {
        if (u != p) {
            dfs(u, v);
            take.pb({dp[u][1], u});
            skip.pb({dp[u][0], u});
            ckmax(dp[v][0], dp[u][1]);
            ckmax(dp[v][1], SZ+max(dp[u][1]-2, dp[u][0]-1));
        }
    }
    sort(take.begin(), take.end(), greater<pi>());
    sort(skip.begin(), skip.end(), greater<pi>());
    ckmax(ans, dp[v][0]);
    ckmax(ans, dp[v][1]);
    // cout << v << " " << dp[v][0] << " " << dp[v][1] << endl;
    if (sz(take) > 1) {
        ckmax(ans, take[0].f+take[1].f-1+max(SZ-3,0));
        ckmax(ans, skip[0].f+skip[1].f+SZ-2);
        if (take[0].s != skip[0].s) ckmax(ans, take[0].f+skip[0].f+SZ-3);
        else {
            ckmax(ans, take[0].f+skip[1].f+SZ-3);
            ckmax(ans, take[1].f+skip[0].f+SZ-3);
        }
    }
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, u, v;
    cin >> n;
    F0R(i, n-1) {
        cin >> u >> v;
        e[u].pb(v);
        e[v].pb(u);
    }
    dfs();
    cout << ans << endl;
    return 0;
}
