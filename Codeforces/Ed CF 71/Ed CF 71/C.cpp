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

#define sz(x) (int)x.size()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, T;
    ll a, b;
    string s;
    cin >> T;
    while (T) {
        cin >> n >> a >> b;
        cin >> s;
        ll dp[n+2][2];
        F0R(i, n) F0R(j, 2) dp[i][j] = (1LL << 60);
        dp[0][0] = 0;
        FOR(i, 1, n+1) {
            if (s[i-1] == '0') dp[i][0] = min(dp[i-1][0], dp[i-1][1]+a+b);
            dp[i][1] = min(dp[i-1][0]+a+b, dp[i-1][1]+b);
            //cout << dp[i][0] << endl;
        }
        ll ans = dp[n][0] + a*n + b*(n+1);
        cout << ans << endl;
        T--;
    }
    return 0;
}
