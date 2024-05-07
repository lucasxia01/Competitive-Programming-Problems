#include <bits/stdc++.h>

#define pi pair<int, int>
#define vi vector<int>
#define vpi vector<pi>
#define pb push_back
#define rep(i, a, b) for(int i = a; i < (b); i++)
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<array<int, 3> > gr[n+1];
    vector<array<int, 4> > es;
    rep(i, 0, m) {
        int a, b, c; cin >> a >> b >> c;
        es.pb({c, i, a, b});
        if (i < n-1) {
            gr[a].pb({b, c, i});
            gr[b].pb({a, c, i});
        }
    }
    sort(es.begin(), es.end());
    vpi ans;
    for (auto e : es) {
        int hi = 0, idx = -1;
        auto dfs = [&](int v, int p, int goal, auto&& dfs) -> bool {
            if (v == goal) return 1;
            for (auto u : gr[v]) {
                if (u[0] == p) continue;
                if (dfs(u[0], v, goal, dfs)) {
                    if (u[1] > hi) {hi = u[1]; idx = u[2];}
                    return 1;
                }
            }
            return 0;
        };
        dfs(e[2], 0, e[3], dfs);
        if (hi > e[0]) {
            ans.pb({idx, e[1]});
            rep(j, 1, n+1)
                for (auto a = gr[j].begin(); a != gr[j].end(); a++) {
                    if ((*a)[2] == idx) {
                        gr[j].erase(a);
                        break;
                    }
                }
            gr[e[2]].pb({e[3], e[0], e[1]});
            gr[e[3]].pb({e[2], e[0], e[1]});
        }
    }
    cout << ans.size() << '\n';
    for (pi p : ans) cout << p.first+1 << " " << p.second+1 << '\n';
}