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

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
#define MAX_N 1000011
#define INF (1<<29) + 123

using namespace std;
int bl[5] = {0, 2, 5, 7, 10};

bool black(int a) {
    a = a % 12;
    rep(i, 5) if (a == bl[i]) return 1;
    return 0;
}
int trans(int a, int b) {
    return black(a) * 2 + black(b);
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int l;
    int t[4];
    int m[4][6][6][13];
    rep(i, 4) rep(j, 6) rep(k, 6) rep (a, 13) m[i][j][k][a] = 10000000;
    int f, s;
    cin >> t[0] >> t[1] >> t[2] >> t[3] >> l;
    rep(i, 4) rep (j, t[i]) {
        cin >> f >> s;
        rep (k, 12) cin >> m[i][f][s][k + 1];
        //cout << "hi " << i << " " << j << " " << count <<  endl;
    }
    int dp[10011][6] = {};
    for (int j = 1; j <= 5; j++) dp[0][j] = 0;
    for (int i = 1; i < l; i++) {
        for (int j = 1; j <= 5; j++) {
            dp[i][j] = 100000000;
        }
    }
    int a[l];
    rep (i, l) cin >> a[i];
    for (int i = 1; i < l; i++) {
        for (int j = 1; j <= 5; j++) {
            for (int k = 1; k <= 5; k++) {
                if (a[i] - a[i - 1] < 0) dp[i][j] = min(dp[i][j], dp[i - 1][k] + m[trans(a[i], a[i - 1])][j][k][abs(a[i] - a[i - 1])]);
                else if (a[i] - a[i - 1] > 0) dp[i][j] = min(dp[i][j], dp[i - 1][k] + m[trans(a[i - 1], a[i])][k][j][abs(a[i] - a[i - 1])]);
            }
            if (a[i] == a[i - 1]) dp[i][j] = dp[i - 1][j];
        }
    }
    // for (int i = 1; i < l; i++) {
    //     for (int j = 1; j <= 5; j++) {
    //       cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    int ans = INF;
    for (int i = 1; i <= 5; i++) ans = min(ans, dp[l - 1][i]);
    cout << ans << endl;
    return 0;
}
