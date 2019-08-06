#include <iostream>
using namespace std;

int main() {
    int n, a[3];
    cin >> n >> a[0] >> a[1] >> a[2];
    int dp[n + 1];
    for (int i = 0; i <= n; i++) dp[i] = 0;
    for (int j = 0; j < 3; j++) {
        if (a[j] <= n) dp[a[j]] = 1;
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            if (i >= a[j] && dp[i - a[j]]) dp[i] = dp[i] = max(dp[i], dp[i - a[j]] + 1);
        }
    }
    cout << dp[n] << endl;
    return 0;
}
