#include <iostream>
#include <set>
#include <utility>
#include <cmath>
#include <cstdlib>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
#define MOD 998244353
using namespace std;

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll n, k;
    cin >> n >> k;
    n = n * 2 + 1;
    ll dp[n][4];
    ll dp2[n][4];
    rep(i, n) rep(j, 4) dp[i][j] = 0;
    rep(i, n) rep(j, 4) dp2[i][j] = 0;
    dp[1][0] = 1LL; dp[1][3] = 1LL; dp[2][1] = 1LL; dp[2][2] = 1LL;
    ll t[4][4] = {{0, 1, 1, 1}, {0, 0, 2, 0}, {0, 2, 0, 0}, {1, 1, 1, 0}};
    for (int l = 1; l < n/2; l++) {
        rep(i, n) rep(j, 4) dp2[i][j] = 0;
        rep(i, n) rep(j, 4) {
            if (dp[i][j]) {
                rep(k, 4) dp2[i + t[j][k]][k] = (dp2[i + t[j][k]][k] + dp[i][j]) % MOD;
            }
        }
        rep(i, n) rep(j, 4) dp[i][j] = dp2[i][j];
    }
    ll sum = 0;
    rep(i, 4) sum += dp[k][i];
    cout << sum % MOD << endl;
    return 0;
}
