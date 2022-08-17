#include <iostream>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

typedef long long ll;
#define F0R(i, n) for (int i = 0; i < n; i++)
#define sz(x) (int)x.size()

const int MX = 2e5+5;
const ll INF = 1LL<<50;

vector<pair<int, ll> > edges[MX];

ll ans[MX];

void dfs(int v=1, int p=0) {
    if ((sz(edges[v]) == 1 && v != 1) || sz(edges[v]) == 0) { // leaf
        ans[v] = 0;
        return;
    }
    for (auto& u: edges[v]) {
        if (u.first != p) {
            dfs(u.first, v);
            ans[v] = min(ans[v], u.second+min((ll)0, ans[u.first]));
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q, u, v; ll c;
    cin >> n >> q;
    
    F0R(i, n-1) {
        cin >> u >> v >> c;
        edges[u].push_back({v, c});
        edges[v].push_back({u, c});
    }
    F0R(i, n+1) ans[i] = INF;
    dfs();
    while (q--) {
        cin >> v;
        cout << ans[v] << '\n';
    }
    return 0;
}
