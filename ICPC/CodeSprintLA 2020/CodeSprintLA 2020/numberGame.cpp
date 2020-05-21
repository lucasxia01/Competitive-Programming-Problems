#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

const int MOD = 24*60;
const int MX = MOD+5;

#define F0R(i, n) for (int i = 0; i < n; i++)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, u, v;
    cin >> n >> m;
    vector<int> edges[n+1];
    F0R(i, m) {
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    int s, e;
    cin >> s >> e;
    int k; cin >> k;
    int f[n+1]; F0R(i, n+1) f[i] = 0;
    F0R(i, k) cin >> v, f[v] = 1;
    queue<int> q; q.push(e);
    int d[n+1];
    F0R(i, n+1) d[i] = -1;
    d[e] = 0;
    int dis = 1<<20;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        // cout << v << endl;
        if (f[v] && d[v] <= dis) {
            cout << "NO" << endl;
            return 0;
        }
        if (dis != 1<<20) continue;
        if (v == s) {
            dis = d[v];
            continue;
        }
        for(auto& u: edges[v]) {
            if (d[u] == -1) {
                d[u] = d[v]+1;
                q.push(u);
            }
        }
    }
    cout << "YES" << endl;
    return 0;
}
