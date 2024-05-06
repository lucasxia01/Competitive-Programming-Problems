#include<bits/stdc++.h>
using namespace std;

#define F0R(i, n) for (int i = 0; i < n; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define INF (1e9 + 7);
int MX = 1e4;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, x; cin >> n >> x;
    int a[n]; 
    rep(i, 0, n) {
        cin >> a[i];
    }
    int dp[n+1][MX];
    F0R(i, n+1) F0R(j, MX) dp[i][j] = -INF;
    dp[0][x] = 0;
    F0R(i, n) F0R(j, MX) {
        if (dp[i][j] < 0) continue;
        dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
        string tmp = to_string(j);
        sort(tmp.begin(), tmp.end());
        do {
            int val = stoi(tmp);
            if (val - a[i] >= 0) {
                dp[i+1][val-a[i]] = max(dp[i+1][val-a[i]], dp[i][j] + 1);
            }
        } while (next_permutation(tmp.begin(), tmp.end()));
    }
    int ans = 0;
    F0R(j, MX) ans = max(ans, dp[n][j]);
    cout << ans << endl;
}