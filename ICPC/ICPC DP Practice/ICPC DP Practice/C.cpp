#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n + 11];
    for (int i = 0; i < n; i++) cin >> a[i];
    int sum = 0;
    int dp[n + 11][2];
    dp[n + 1][1] = 0; dp[n + 1][0] = 0;
    for (int i = n; i >= 0; i--) {
        sum += a[i];
        dp[i][0] = max(dp[i + 1][1] + a[i], dp[i + 1][0]);
        dp[i][1] = min(dp[i + 1][1] + a[i], dp[i + 1][0]);
    }
    cout << sum - dp[0][0] << " " << dp[0][0] << endl;
    return 0;
}
