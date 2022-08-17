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
const int MX = 2e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, u;
    cin >> n;
    vi edges[MX];
    F0R(i, n-1) {
        cin >> u;
        edges[u].pb(i+2);
    }
    ll dp[n+1][3]; // 0 is colorless, 1 is colored but still needs a partner, 2 is colored (can extend upwards)
    F0R(i, n+1) F0R(j, 3) dp[i][j] = 0;
    FORd(i, 1, n) {
        if (sz(edges[i]) == 0) { // leaf case, has to be colored
            dp[i][0] = 0; dp[i][1] = 0; dp[i][2] = 1;
            continue;
        }
        dp[i][0] = 1; // with no children, it can only be colorless
        trav(a, edges[i]) { // add in children one by one
            // dp[i][x] stores the current calculation with the processed children of this node
            // for the colored case, we consider when its colored and still needs a match (dp[i][1]), then the current child can choose to match it with either (dp[a][1|2]), the other case is that the node has already been colored (dp[i][2]) and the current node can either not match it (colorless dp[a][0] or colored dp[a][2]), or match it (dp[a][1] or dp[a][2])
            // Note that dp[a][2] is repeated twice because it can either be the same color as the node (and match it), or different (don't match)
            dp[i][2] = ((dp[i][1] * (dp[a][1] + dp[a][2]))%MOD + (dp[i][2]*(dp[a][0] + dp[a][1] + 2*dp[a][2]))%MOD)%MOD;
            // for the case where the current node needs a partner, if the current node already needs a partner (dp[i][1], don't match it (dp[a][0] or dp[a][2] (different color)), or if the current node is colorless (dp[i][0]), we can make it need a partner with dp[a][1] or dp[a][2].
            dp[i][1] = ((dp[i][1] * (dp[a][0] + dp[a][2]))%MOD + (dp[i][0] * (dp[a][1] + dp[a][2]))%MOD)%MOD;
            // for colorless current node, we can only keep it colorless if it was colorless before (dp[i][0]) and if we don't color it with the current child (dp[a][0] or dp[a][2] where we have a different color)
            dp[i][0] = (dp[i][0] *(dp[a][0] + dp[a][2])) % MOD;
        }
    }
    cout << (dp[1][0]+dp[1][2])%MOD << endl;
    return 0;
}
