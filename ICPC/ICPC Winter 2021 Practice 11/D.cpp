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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int r, c, n; cin >> r >> c >> n;
    int m[r][c]; F0R(i, r) F0R(j, c) cin >> m[i][j];
    int dp[r][c+1][n+1]; F0R(i, r) F0R(j, c+1) F0R(k, n+1) dp[i][j][k] = INF;
    F0R(i, r) dp[i][0][0] = 0;
    bool pass[r][c]; 
    F0R(i, r) F0R(j, c) {
        if (i == 0 || i == r-1 || j == 0 || j == c-1) pass[i][j] = 0;
        else {
            if (m[i-1][j] == -1 || m[i+1][j] == -1 || m[i][j-1] == -1 || m[i][j+1] == -1) pass[i][j] = 0;
            else {
                pass[i][j] = (m[i-1][j] > m[i][j] && m[i+1][j] > m[i][j] && m[i][j-1] < m[i][j] && m[i][j+1] < m[i][j]);
            }
        }
    }


    F0R(j, c) F0R(i, r) F0R(k, n+1) {
        if (dp[i][j][k] == INF) continue;
        F0R(dr, 3) {
            int DR = dr-1;
            if (i+DR < 0 || i+DR >= r) continue;
            if (m[i+DR][j] == -1) continue;
            if (k+pass[i+DR][j] > n) continue;
            ckmin(dp[i+DR][j+1][k+pass[i+DR][j]], dp[i][j][k]+m[i+DR][j]);
            // dbg(i, j, k, dp[i][j][k]);
        }
    }
    int ans = INF;
    F0R(i, r) ckmin(ans, dp[i][c][n]);
    if (ans == INF) cout << "impossible" << nl;
    else cout << ans << nl;
    return 0;
}