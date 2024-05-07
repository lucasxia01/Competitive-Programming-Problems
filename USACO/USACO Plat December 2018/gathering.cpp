#include <bits/stdc++.h>
using namespace std;

const int MX = 1e5;
int n, m;
vector<int> gr[MX+1]; // adj list
vector<int> dgr[MX+1]; // directed adj list
vector<int> orders[50000];
queue<int> q;
vector<bool> ans;
void dfs(int v, int p) {
    if (dgr[v].size()) return;
    ans[v] = 1;
    for (int u : gr[v]) {
        if (u == p) continue;
        dfs(u, v);
    }
}
int main() {
    freopen("gathering.in", "r", stdin);
    freopen("gathering.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n-1; i++) {
       int a, b;
       cin >> a >> b;
       gr[a].push_back(b);
       gr[b].push_back(a);
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        dgr[a].push_back(b);
    }
    // process until no directed edges
    int dcnt = m;
    ans.resize(n+1, 0);
    int inCnt[n+1], dInCnt[n+1]; 
    memset(inCnt, 0, sizeof(inCnt));
    memset(dInCnt, 0, sizeof(dInCnt));
    for (int i = 1; i <= n; i++) {
        for (int v: dgr[i]) dInCnt[v]++;
        inCnt[i] = (gr[i]).size();
    }
    for (int i = 1; i <= n; i++) {
        if (dInCnt[i] == 0 && inCnt[i] == 1) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int v = q.front(); q.pop();
        // cerr << v << '\n';
        ans[v] = 0;
        for (int u : dgr[v]) {
            dInCnt[u]--;
            dcnt--;
            if (dInCnt[u] == 0 && inCnt[u] == 1) {
                q.push(u);
            }
        }
        for (int u : gr[v]) {
            inCnt[u]--;
            if (dInCnt[u] == 0 && inCnt[u] == 1) {
                q.push(u);
            }
        }
        if (dcnt == 0) break;
    }
    if (dcnt) {
        for (int i = 1; i <= n; i++) cout << 0 << '\n';
    } else {
        assert(q.size());
        int v = q.front();
        // dfs from v
        dfs(v, -1);
        for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
    }
    return 0;
}

