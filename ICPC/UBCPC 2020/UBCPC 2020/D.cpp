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
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
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

const int MX = 2000+5;
int a[MX];
int n, K;
ll MOD;
 
ll modAdd(ll x, ll y) {
    return ( (x % MOD + y % MOD) % MOD + MOD ) % MOD;
}

ll dp[MX][MX][2][8]; // current position, rank, direction, length of run
ll pref[MX][MX][2][8];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> K >> MOD;
    F0R(i, MX) F0R(k, 2) dp[0][i][k][1] = 1;
    F0R(i, n-1) {
        F0R(j, n) F0R(k, 2) FOR(l, 1, K) pref[i][j+1][k][l] = (pref[i][j][k][l] + dp[i][j][k][l]) % MOD;
        F0R(j, n-i-1) {
            FOR(l, 1, K) dp[i+1][j][0][2] = modAdd(dp[i+1][j][0][2], modAdd(-pref[i][j+1][1][l], pref[i][n-1-i+1][1][l]));
            FOR(l, 2, K-1) dp[i+1][j][0][l+1] = modAdd(dp[i+1][j][0][l+1], modAdd(-pref[i][j+1][0][l], pref[i][n-1-i+1][0][l]));
            FOR(l, 1, K) dp[i+1][j][1][2] = modAdd(dp[i+1][j][1][2], pref[i][j+1][0][l]);
            FOR(l, 2, K-1) dp[i+1][j][1][l+1] = modAdd(dp[i+1][j][1][l+1], pref[i][j+1][1][l]);
        }
    }
    ll ans = 0;
    F0R(k, 2) F0R(l, K+1) ans = modAdd(ans, dp[n-1][0][k][l]);
    cout << ans << nl;
    return 0;
}
