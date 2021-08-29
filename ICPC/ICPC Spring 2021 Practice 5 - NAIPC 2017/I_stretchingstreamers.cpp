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
#include <climits>

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
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int gcd(int a, int b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a%b);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int a[n]; F0R(i, n) cin >> a[i];
    bool m[n][n];
    F0R(i, n) F0R(j, n) m[i][j] = (gcd(a[i], a[j]) != 1);
    ll dp[n][n], dp2[n][n];
    F0R(i, n) F0R(j, n) dp[i][j] = dp2[i][j] = 0;
    F0R(i, n) dp[i][(i+1)%n] = dp2[i][(i+1)%n] = 1;
    FOR(len, 2, n-1) {
        F0R(i, n) {
            int k = (i+len)%n;
            int k1 = (i+len-1)%n;
            FOR(J, i+1, i+len-1) {
                int j = J%n;
                if (!m[j][k]) continue;
                dp2[i][k] = ((dp[j][k]*dp2[i][j])%MOD + dp2[i][k])%MOD;
            }

            // i  to i+len
            FOR(J, i+1, i+len-1) {
                int j = J%n;
                if (!m[i][j]) continue;
                dp[i][k] = ((dp[i][j]*dp[j][k])%MOD + dp[i][k])%MOD;
                // if (i == 1 && k == 3) dbg("hi", j, dp[i][j], dp[j][k]);
            }
            // dbg(i, k, dp[i][k], dp2[i][k]);
            dp[i][k] = (dp[i][k] + dp2[i][k])%MOD;
        }
    }
    ll ans = 0;
    FOR(i, 1, n-1) {
        if (!m[0][i]) continue;
        // dbg(dp2[0][i], dp[i][0]);
        ans = ((dp2[0][i]*dp[i][0])%MOD + ans)%MOD;
    }
    cout << ans << nl;
    return 0;
}
