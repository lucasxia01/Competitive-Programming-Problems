#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;

    long long dp[s.length()][5];
    for (int j = 0; j < 5; j++)
        dp[0][j] = 0;
    if (s[0] == 'v') dp[0][0] = 1;
    for (int i = 1; i < s.length(); i++) {
        for (int j = 0; j < 5; j++)
            dp[i][j] = dp[i-1][j];
        if (s[i] == 'v') {
            dp[i][0] = 1;
            dp[i][1] = dp[i-1][1]+dp[i-1][0];
            dp[i][3] = dp[i-1][2];
            dp[i][4] = dp[i-1][4]+dp[i-1][3];
        } else {
            dp[i][0] = 0;
            dp[i][2] = dp[i-1][2]+dp[i-1][1];
            dp[i][3] = 0;
        }
//        for (int j = 0; j < 5; j++)
//            cout << dp[i][j] << " ";
//        cout << endl;
    }
    cout << dp[s.length() - 1][4] << endl;
    
    return 0;
}
