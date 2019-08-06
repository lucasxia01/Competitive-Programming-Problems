//
//  main.cpp
//  Lost Traveler
//
//  Created by Lucas Xia on 3/1/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;

#define int long long
#define MOD 1000000007

int n, m;
int adjM[1011][1011];
bool visited[1011];
int dp[1011];

bool dfs(int v) {
    if (v == n) return true;
    if (visited[v]) return false;
    visited[v] = 1;
    for (int i = 1; i <= n; i++) {
        if (adjM[v][i] && dfs(i))
            return true;
    }
    return false;
}

int solve(int s) {
    if (s == n) return 0;
    int ans = 0;
    if (adjM[s][n]) ans++;
    for (int i = 1; i <= n; i++) {
        if (adjM[s][i]) {
            if (dp[i] == -1) dp[i] = solve(i)%MOD;
            ans += dp[i]%MOD;
            ans %= MOD;
        }
    }
    dp[s] = ans;
    return ans;
}

int32_t main() {
    int t, s, e;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n >> m;
        for (int j = 0; j < 1011; j++) {
            visited[j] = false;
            for (int k = 0; k < 1011; k++) {
                adjM[j][k] = 0;
            }
        }
        for (int j = 0; j < m; j++) {
            cin >> s >> e;
            adjM[s][e]++;
        }
        if (!dfs(1)) {
            cout << 0 << endl;
            continue;
        }
        //top sort
        
        unordered_map<int, int> edgeCount;
        vector<int> order;
        vector<int> zeros;
        int count = 0;
        for (int j = 1; j <= n; j++) {
            count = 0;
            for (int k = 1; k <= n; k++)
                if (adjM[k][j]) count++;
            if (count == 0) zeros.push_back(j);
            else edgeCount.insert(make_pair(j, count));
        }
        
        for (int j = 0; j < n; j++) {
            if (zeros.size() == 0) break;
            int id = zeros.at(0);
            order.push_back(id);
            zeros.erase(zeros.begin());
            for (unordered_map<int, int>::iterator it = edgeCount.begin(); it != edgeCount.end();) {
                if (adjM[id][it->first]) it->second--;
                if (it->second == 0) {
                    zeros.push_back(it->first);
                    it = edgeCount.erase(it);
                } else it++;
            }
        }
        if (order.size() != n) {
            cout << -1 << endl;
            continue;
        }
        for (int j = 0; j < 1011; j++) dp[j] = -1;
        cout << solve(1) << endl;
    }
    return 0;
}
