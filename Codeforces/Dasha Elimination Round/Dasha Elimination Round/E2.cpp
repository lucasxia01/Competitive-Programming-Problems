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
    int t, n, m, sum
    ;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        int b[n][m],a[n][m];
        vpi bestCols;
        F0R(i, n) F0R(j, m) cin >> b[i][j];
        F0R(i, m) {
            int maxV = 0;
            F0R(j, n) {
                maxV = max(maxV, b[j][i]);
            }
            bestCols.pb(mp(maxV, i));
        }
        sort(bestCols.begin(), bestCols.end());
        FORd(i, max(m-n, 0), m) {
            F0R(j, n) {
                a[j][m-i-1] = b[j][bestCols[i].s];
            }
        }
        int o = min(m, n);
        int best[o][1<<n];
        F0R(i, o) {
            F0R(mask, 1<<n) {
                best[i][mask] = 0;
                F0R(shift, n) {
                    sum = 0;
                    for (int pow = 1, c = 0; c < n; pow<<=1, c++) {
                        if (pow&mask) sum += a[(c+shift)%n][i];
                    }
                    best[i][mask] = max(best[i][mask], sum);
                }
            }
        }
        int dp[o+1][1<<n];
        F0R(mask, 1<<n) dp[0][mask] = 0;
        F0R(i, o) {
            F0R(mask, 1<<n) {
                dp[i+1][mask] = dp[i][0]+best[i][mask];
                for (int s = mask; s; s = ((s-1) & mask)) {
                    dp[i+1][mask] = max(dp[i+1][mask], dp[i][s]+best[i][mask^s]);
                }
            }
        }
        cout << dp[o][(1<<n)-1] << endl;
    }
    return 0;
}
