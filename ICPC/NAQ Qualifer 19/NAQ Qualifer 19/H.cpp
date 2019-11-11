#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cmath>
#define ll long long

#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define F0Rd(i, n) for (int i = n-1; i >= 0; i--)

using namespace std;

int main() {
    int n;
    cin >> n;
    int mat[n][n];
    F0R(i, n) F0R(j, n) cin >> mat[i][j];
    vector<pair<int, int>> edges;
    int dp[n][n];
    F0R(i, n) F0R(j, n) dp[i][j] = 0;
    FOR(len, 2, n) {
        F0R(i, n) {
            int j = (i+len-1)%n;
            int best = 0;
            if (mat[i][j]) {
                best = 1;
                if (len > 2) best += dp[i+1][(j-1+n)%n];
            }
            F0R(k, len) {
                best = max(best, dp[i][(i+k)%n] + dp[(i+k+1)%n][j]);
            }
            dp[i][j] = best;
        }
    }
//    F0R(i, n) {
//        F0R(j, n) {
//            cout << j << " " << i << " " << dp[j][i] << endl;
//        }
//    }
    cout << dp[0][n-1] << endl;
    return 0;
}
