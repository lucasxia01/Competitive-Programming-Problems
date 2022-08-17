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

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

const int MX = 505;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    int a[n];
    F0R(i, n) cin >> a[i];
    /*
     idea here is that the answer is a partition of the array
     such that each section is reducible to one unique number
     */
    int dp[MX][MX];
    F0R(i, MX) F0R(j, MX) dp[i][j] = -1;
    // here we compute if each section can be reduced by checking
    // ranges from [i,j) and [j,i+l) to see if they are reduced to same #
    FOR(l, 1, n) {
        F0R(i, n-l+1) {
            if (l == 1) dp[i][i+l] = a[i];
            FOR(j, 1, l-1) {
                if (dp[i][i+j] == dp[i+j][i+l] && dp[i][i+j] != -1)
                    dp[i][i+l] = dp[i][i+j]+1;
            }
            //cout << i << " " << i+l << " " << dp[i][i+l] << endl;
        }
    }
    int dp2[MX]; // this computes the answer for the prefix
    F0R(i, MX) dp2[i] = INF;
    dp2[0] = 0;
    FOR(i, 1, n) {
        F0R(j, i) {
            if (dp[j][i] != -1)
                dp2[i] = min(dp2[i], dp2[j]+1);
        }
    }
    cout << dp2[n] << endl;
    return 0;
}
