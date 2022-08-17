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

const int MX = 45;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("ssh.in", "r", stdin);
//    freopen("ssh.out", "w", stdout);
    int l, m; cin >> l >> m;
    int a[l-1]; F0R(i, l-1) cin >> a[i];
    int t[m][m]; F0R(i, m) F0R(j, m) cin >> t[i][j];
    pair<int, int> dp[l][m]; // prev, curAns
    F0R(i, m) dp[0][i] = {-1, 0};
    FOR(i, 1, l-1) F0R(j, m) dp[i][j] = {-1, INF};
    F0R(i, l-1) {
        F0R(j, m) {
            F0R(k, m) {
                if (dp[i+1][k].s > dp[i][j].s+abs(a[i]-t[j][k])) {
                    dp[i+1][k] = {j, dp[i][j].s+abs(a[i]-t[j][k])};
//                    cout << i+1 << " " << k << " " << j << " " << dp[i+1][k].s << " " << dp[i][j].s << nl;
                }
            }
        }
    }
    int bestIdx = -1;
    int minAns = INF;
    F0R(i, m) if (ckmin(minAns, dp[l-1][i].s)) bestIdx = i;
    string ans = "";
    int curL = l-1;
    while (bestIdx != -1) {
        ans += ('a'+bestIdx);
        bestIdx = dp[curL][bestIdx].f;
        curL--;
    }
    assert(curL == -1);
    reverse(ans.begin(), ans.end());
    cout << ans << nl;
    return 0;
}
