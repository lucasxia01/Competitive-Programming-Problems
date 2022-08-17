#include <iostream>
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
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define trav(a, x) for (auto& a : x)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }


const int MX = 450*100/2+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    int a[n];
    int total = 0;
    F0R(i, n) { cin >> a[i]; total += a[i]; }
    bool dp[n+1][n/2+2][MX]; F0R(i, n+1) F0R(j, n/2+2) F0R(k, MX) dp[i][j][k] = 0;
    dp[0][0][0] = 1;
    F0R(i, n) F0R(j, n/2+2) F0R(k, MX) {
        if (dp[i][j][k] == 0) continue;
        dp[i+1][j][k] = 1;
        if (a[i]+k >= MX || j+1 >= n/2+2) continue;
        dp[i+1][j+1][k+a[i]] = 1;
    }
    int ans = 0;
    F0R(k, MX) {
        if (dp[n][n/2][k]) {
            if (k*2 > total) continue;
            else ckmax(ans, k*2);
        }
        if (n%2) {
            if (dp[n][n/2+1][k]) {
                if (k*2 > total) continue;
                else ckmax(ans, k*2);
            }
        }
    }
    cout << ans/2 << " " << total-ans/2 << '\n';
    return 0;
}
