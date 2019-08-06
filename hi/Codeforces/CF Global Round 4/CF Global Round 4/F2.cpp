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
    int n, m;
    cin >> n >> m;
    int colors[n];
    int idx[n];
    for (int i = 0; i < n; i++) {
        cin >> colors[i];
        idx[colors[i] - 1] = i;
    }
    int minIdx[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int min = n+1;
            minIdx[i][j] = -1;
            for (int k = i; k <= j; k++) {
                if (colors[k] < min) {
                    min = colors[k];
                    minIdx[i][j] = k;
                    //cout << i << " " << j << ": " << k << endl;
                }
            }
        }
    }
    
    long long dp[m+1][m+1], sum = 0, sum1 = 0, a, b; // left, right not inclusive
    for (int length = 0; length <= m; length++) {
        for (int i = 0; i + length <= m; i++) {
            dp[i][i+length] = 1;
            if (length == 0) continue;
            
            sum = 0;
            int j = minIdx[i][i+length-1];
            //cout << j << endl;
            for (int k = i; k <= j; k++) {
                a = dp[i][k];
                b = dp[k][j];
                sum = (sum+(a*b)%MOD)%MOD;
            }
            //cout << i << " " << i+length << ": " << sum << endl;
            
            sum1 = 0;
            for (int k = j+1; k <= i+length; k++) {
                a = dp[k][i+length];
                b = dp[j+1][k];
                sum1 = (sum1+(a*b)%MOD)%MOD;
            }
            //cout << i << " " << i+length << ": " << sum1 << endl;
            dp[i][i+length] = (sum*sum1)%MOD;
        }
    }
    //cout << minIdx[0][m-1] << endl;
    cout << dp[0][m] << endl;
    
    return 0;
}
