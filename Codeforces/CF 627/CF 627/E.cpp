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
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, h, l, r;
    cin >> n >> h >> l >> r;
    int a[n];
    F0R(i, n) cin >> a[i];
    int dp[n+1][h];
    F0R(i, n+1) F0R(j, h) dp[i][j] = -INF;
    dp[0][0] = 0;
    FOR(i, 1, n) {
        F0R(j, h) {
            int temp = j-a[i-1]+h;
            if (j >= l && j <= r)
                dp[i][j] = max(dp[i][j], dp[i-1][temp%h]+1);
            else dp[i][j] = max(dp[i][j], dp[i-1][temp%h]);
            temp = (temp+1)%h;
            if (j >= l && j <= r)
            dp[i][j] = max(dp[i][j], dp[i-1][temp%h]+1);
            else dp[i][j] = max(dp[i][j], dp[i-1][temp%h]);
            //cout << dp[i][j] << " ";
        }
        //cout << endl;
    }
    int ans = 0;
    F0R(i, h) ans = max(ans, dp[n][i]);
    cout << ans << endl;
    return 0;
} // CHANGE BACK THE INF CONST

/*
 7 24 21 23
 16 17 14 20 20 11 22

 0 16 9 23 19 15 2 0
15-16
7-9
20-23
15-19
10-15
20-2
17-0
 */
