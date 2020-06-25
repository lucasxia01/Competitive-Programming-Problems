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
#include <random>
#include <chrono>
#include <cassert>

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
#define sz(x) (int)x.size()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 205*205;

vi edges[MX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("restore.in", "r", stdin);
//    freopen("restore.out", "w", stdout);
    int n; cin >> n;
    int a[n][n];
    F0R(i, n) F0R(j, n) cin >> a[i][j];
    int num_nodes = n;
    int dist[n][MX]; F0R(i, n) F0R(j, MX) dist[i][j] = -1;
    dist[0][0] = 0;
    vpi edges;
    vi gr[MX];
    FOR(i, 1, n-1) {
        // we currently have all distances up to i
        int node = -1;
        if (i == 1) node = 0;
        else {
            vi pos;
            FOR(j, n, num_nodes-1) { // check if any node works between 0 and 1 to restruct search space
                if (a[0][i]-dist[0][j]==a[1][i]-dist[1][j] && a[0][i]-dist[0][j]>0) pos.pb(j);
            }
            trav(p, pos) { // should be at most MX p
                int d = a[0][i]-dist[0][p];
                bool ok = 1;
                F0R(j, i) {
                    if (a[j][i]-dist[j][p]!=d) {
                        ok = 0;
                        break;
                    }
                }
                if (ok) { node = p; break; }
            }
            if (node == -1) { // no possible node
                cout << -1 << nl;
                return 0;
            }
        }
        if (a[0][i]-dist[0][node] == 1) {
            F0R(j, i) dist[j][i] = dist[j][node]+1;
            gr[i].pb(node);
            gr[node].pb(i);
            if (i < node) edges.pb({i, node});
            else edges.pb({node, i});
        } else {
            F0R(j, i) dist[j][num_nodes] = dist[j][node]+1;
            edges.pb({node, num_nodes});
            gr[node].pb(num_nodes);
            gr[num_nodes].pb(node);
            F0R(j, a[0][i]-dist[0][node]-2) {
                F0R(jj, i) dist[jj][num_nodes+1] = dist[jj][num_nodes]+1;
                gr[num_nodes+1].pb(num_nodes);
                gr[num_nodes].pb(num_nodes+1);
                edges.pb({num_nodes, num_nodes+1});
                num_nodes++;
            }
            F0R(j, i) dist[j][i] = dist[j][num_nodes]+1;
            gr[i].pb(num_nodes);
            gr[num_nodes].pb(i);
            edges.pb({i, num_nodes++});
        }
        queue<int> q; q.push(i); // setting distances from i to everything else in the graph
        bool vis[num_nodes]; F0R(j, num_nodes) vis[j] = 0;
        vis[i] = 1;
        dist[i][i] = 0;
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            trav(v, gr[cur]) {
                if (vis[v]) continue;
                vis[v] = 1;
                dist[i][v] = dist[i][cur]+1;
                q.push(v);
            }
        }
    }
    
    sort(edges.begin(), edges.end());
    assert(num_nodes==sz(edges)+1);
    cout << num_nodes << nl;
    trav(e, edges) cout << e.f+1 << " " << e.s+1 << nl;
    return 0;
}
