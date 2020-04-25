#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define F0R(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define FORd(i,a,b) for (int i = (b); i >= (a); i--)
#define trav(a, x) for (auto& a : x)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound

const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}
const int MX = 1e5+5;
int n, m;
vi adj[MX], adjR[MX];
bool vis[MX];
vi topsort, component;
ll ans = 0;

// dfs1 builds the reverse topological sort ordering of a directed graph
// that could have cycles, in the cases with cycles, their ordering is dependent on the graph, and is not necessarily consecutive in the ordering
// the ordering is essentially based on time exiting each node
void dfs1(int u) {
    vis[u] = 1;
    trav(v, adj[u]) {
        if (!vis[v]) dfs1(v);
    }
    topsort.pb(u);
}

ll dfs2(int u) {
    vis[u] = 1;
    ll count = 0;
    trav(v, adjR[u]) {
        if (!vis[v]) count += dfs2(v);
    }
    component.pb(u);
    return count+1;
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    int u, v;
    F0R(i, m) {
        cin >> u >> v;
        adj[u].pb(v);
        adjR[v].pb(u); // reverse graph
    }
    F0R(i, n) if (!vis[i]) dfs1(i);
    memset(vis, 0, MX);
    ll sum = 0;
    F0Rd(i, n) { // go backwards through the ordering, but also use the reverse graph
        if (!vis[topsort[i]]) {
            ll ret = dfs2(topsort[i]);
            // cout << topsort[i] << " " << ret << endl;
            ans += sum * ret;
            sum += ret;
            trav(u, component) {
                trav(v, adj[u]) {
                    if (!vis[v]) ans--;
                }
            }
            component.clear();
        }
    }
    cout << ans << endl;
    return 0;
}
