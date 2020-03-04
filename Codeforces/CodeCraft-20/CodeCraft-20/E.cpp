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
const int MX = 1<<20;
const ll INF = (1LL<<50) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, p, k;
    cin >> n >> p >> k;
    ll a[n], s[n][p];
    F0R(i, n) cin >> a[i];
    F0R(i, n) F0R(j, p) cin >> s[i][j];
    vl m[n+1];
    F0R(i, p+1) m[0].pb(0);
    F0R(i, n) {
        m[i+1].pb(a[i]);
        F0R(j, p) {
            m[i+1].pb(s[i][j]);
        }
    }
    sort(m+1, m+n+1, greater<vl>());
    ll dp[n+1][1<<p];
    F0R(i, n) {
        F0R(j, 1<<p) dp[i][j] = -INF;
    }
    dp[0][0] = 0;
    FOR(i, 1, n) {
        F0R(j, 1<<p) {
            int count = 0;
            F0R(l, p) if (j&(1<<l)) count++;
            if (i > k+count) dp[i][j] = dp[i-1][j];
            else dp[i][j] = dp[i-1][j] + m[i][0];
            F0R(l, p) {
                if (j&(1<<l)) {
                    if (dp[i][j] < dp[i-1][j-(1<<l)] + m[i][l+1]) {
                        dp[i][j] = dp[i-1][j-(1<<l)] + m[i][l+1];
                    }
                }
            }
//            bitset<2> x(j);
//            cout << i << " " << x << " " << dp[i][j] << endl;
        }
    }
    cout << dp[n][(1<<p)-1] << endl;
    return 0;
}
