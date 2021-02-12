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
    int p, q; cin >> p >> q;
    int dp[101][101][2];
    F0R(i, 101) F0R(j, 101) {
        dp[i][j][0] = -INF;
        dp[i][j][1] = INF;
    }
    F0R(i, 101) F0R(j, 2) dp[i][0][j] = dp[0][i][j] = 0;
    FOR(i, 1, p) FOR(j, 1, q) F0R(k, 2) {
        if (k == 0) {
            int ok = 2*((i+j)%2 == (p+q)%2)-1;
            F0R(jj, j) ckmax(dp[i][j][k], dp[i][jj][k^1]+(ok*((j-jj)%2)*(i%2)));
        } else {
            int ok = 2*((i+j)%2 == (p+q)%2)-1;
            F0R(ii, i) ckmin(dp[i][j][k], dp[ii][j][k^1]+(-ok*((i-ii)%2)*(j%2)));
        }
    }
//    F0R(i, p+1) {
//        F0R(j, q+1) cout << dp[i][j][0] <<" "; cout << nl;
//    }
    cout << dp[p][q][0] << nl;
    return 0;
}
