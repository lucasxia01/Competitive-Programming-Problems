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

const int MX = 1<<20;

int n, m;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("dominoes.in", "r", stdin);
//    freopen("dominoes.out", "w", stdout);
    cin >> n >> m;
    int N = 1<<(2*n);
    ll dp[2][N];
    F0R(i, 2) F0R(j, N) dp[i][j] = 0;
    dp[0][0] = 1;
    F0R(i, m) {
        F0R(j, 1<<n) {
            int mk = j^((1<<n)-1);
            for (int cMask = mk; ; cMask = mk&(cMask-1)) {
                int cm = 0;
                bool ok = 1;
                int tempM = cMask|(j&((1<<n)-1));
                F0R(k, n) {
                    if ((tempM&(1<<k)) == 0) {
                        if (k+2 >= n || (tempM&(1<<(k+1))) || (tempM&(1<<(k+2)))) {
                            ok = 0;
                            break;
                        }
                        k += 2;
                    } else if (cMask&(1<<k)) {
                        cm += 1<<k;
                        cm += 1<<(k+n);
                    }
                }
                if (!ok) {
                    if (cMask == 0) break;
                    continue;
                }
                int mask = j&((1<<n)-1);
                for (int curMask = mask; ; curMask = mask&(curMask-1)) {
                    int M = (curMask<<n)+j;
                    dp[1][curMask+cm] += dp[0][M];
                    if (curMask == 0) break;
                }
                if (cMask == 0) break;
            }
        }
        F0R(j, N) {
            dp[0][j] = dp[1][j];
            dp[1][j] = 0;
        }
    }
    cout << dp[0][0] << nl;
    return 0;
}
