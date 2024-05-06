#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<int> color(n+1); // 0 white 1 black
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }

    vector<vector<int>> adj(n+1);
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    function<array<int, 2>(int, int)> dfs = [&](int v, int p) {
        if (adj[v].size() == 1 && v != 1) {
            array<int, 2> arr = {0, 0};
            arr[1-color[v]] = 1;
            return arr;
        }
        vector<array<int, 2>> res, dp;
        for (int x : adj[v]) {
            if (x == p) continue;
            res.push_back(dfs(x, v));
        }
        dp.resize(res.size()+1);
        dp[0][1] = -1000000007;
        for (int i = 1; i <= res.size(); i++) {
            dp[i][0] = max(dp[i-1][0]+res[i-1][0], dp[i-1][1]+res[i-1][1]);
            dp[i][1] = max(dp[i-1][0]+res[i-1][1], dp[i-1][1]+res[i-1][0]);
        }
        //cout << v << ' ' << dp.back()[0] << ' ' << dp.back()[1] << '\n';
        dp.back()[1-color[v]]++;
        return dp.back();
    };

    auto res = dfs(1, -1);
    cout << max(res[0], res[1]) << '\n';
}