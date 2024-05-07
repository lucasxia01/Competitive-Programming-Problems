#include <bits/stdc++.h>

#define int long long
using namespace std;

const int INF = 1e9+100;

signed main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<array<int, 3> > v(n);
        for (int i = 0; i < n; i++) {
            int a, b, d; cin >> a >> b >> d;
            v[i] = {a, b, d};
        }
        // coordinate compression
        map<int, int> m;
        for (int i = 0; i < n; i++) {
            m[v[i][0]] = 0;
            m[v[i][1]] = 0;
        }
        int cnt = 0;
        for (auto [a, b] : m) m[a] = cnt++;
        int N = m.size();
        int dp[N+1][N+1];
        for (int i = 0; i < N+1; i++) {
            for (int j = 0; j < N+1; j++) {
                dp[i][j] = INF;
            }
            dp[i][i] = 0;
        }
        for (auto& [a, b, d] : v) {
            a = m[a];
            b = m[b];
        }
        for (int len = 0; len < N; len++) {
            for (int i = 0; i+len < N; i++) {
                // splitting point
                // find the max power in this zone
                int hi = 0;
                for (auto [a, b, d] : v) {
                    if (a >= i && b <= i+len) {
                        hi = max(hi, d);
                    }
                }
                for (int j = i; j <= i+len; j++) {
                    // cerr << i << " " << j << " " << i+len+1 << endl;
                    dp[i][i+len+1] = min(dp[i][i+len+1], dp[i][j] + dp[j+1][i+len+1] + hi);
                }
            }
        }
        cout << dp[0][N] << endl;
    }
}