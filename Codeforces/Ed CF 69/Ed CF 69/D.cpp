#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <utility>
#define MOD 998244353

using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n, m, k;
    cin >> n >> m >> k;
    long long a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long dp[n][m+1];
    long long maxCost = 0;
    for (int i = 0; i < n; i++) {
        dp[i][1] = a[i] - k;
        if (i > 0 && i >= m) dp[i][1] = max(dp[i][1], dp[i-1][m] + a[i] - k);
        maxCost = max(maxCost, dp[i][1]);
        for (int j = 2; j <= m && j <= i+1; j++) {
            dp[i][j] = 0;
            if (i > 0) dp[i][j] = dp[i-1][j-1] + a[i];
            maxCost = max(maxCost, dp[i][j]);
        }
        
    }
    cout << maxCost << endl;
    
    return 0;
}
