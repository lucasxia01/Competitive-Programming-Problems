#include <vector>
#include <stack>
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <functional>
#include <set>
#include <cstring>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>

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
const ll INF_LL = 1000000000000000000;
#define sz(x) (int)x.size()

ll a[300011], b[300011];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int q, n;
    cin >> q;
    while (q) {
        cin >> n;
        F0R(i, n) cin >> a[i] >> b[i];
        ll dp[n][3];
        dp[0][0] = 0;
        dp[0][1] = b[0];
        dp[0][2] = b[0]*2;
        FOR(i, 1, n) {
            F0R(j, 3) {
                ll m = INF_LL;
                F0R(k, 3) {
                    if (a[i]+j != a[i-1]+k) m = min(m, dp[i-1][k]);
                }
                dp[i][j] = m+b[i]*j;
            }
        }
        cout << min(dp[n-1][0], min(dp[n-1][1], dp[n-1][2])) << endl;
        q--;
    }
    return 0;
}
