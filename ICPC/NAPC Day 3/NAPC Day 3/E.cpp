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

const int MX = 3e5+5;

struct edge {
    int u, v, p;
    bool operator<(edge const& other) const {
        return (p > other.p);
    }
};

vi adj[MX], curAdj[MX];
int degCount[MX];
int marked[MX], loop[MX], marked2[MX];
pi ans[MX];
int n, m;
int zeroCount = 0;
int twoCount = 0;
int edgeCount = 0;
int loopCount = 0;

void dfs(int v) {
    if (loop[v]) {
        loop[v] = 0;
        loopCount--;
    }
    marked[v] = 1;
    trav(u, curAdj[v]) {
        if (marked[u]) continue;
        dfs(u);
    }
}

bool dfs2(int v) {
    if (degCount[v] != 2) return false;
    marked2[v] = 1;
    trav(u, curAdj[v]) {
        if (marked2[u]) continue;
        if (!dfs2(u)) {
            marked2[v] = 0;
            return false;
        }
    }
    marked2[v] = 0;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    vector<edge> edges(m);
    F0R(i, m) {
        cin >> edges[i].u >> edges[i].v >> edges[i].p;
        adj[edges[i].u].pb(edges[i].v);
        adj[edges[i].v].pb(edges[i].u);
    }
    sort(edges.begin(), edges.end());
    int q, p;
    cin >> q;
    vpi queries;
    F0R(i, q) {
        cin >> p;
        queries.pb(mp(p, i));
    }
    sort(queries.begin(), queries.end(), greater<pi>());
    int j = 0;
    zeroCount = n;
    F0R(i, q) {
        while (j < m && edges[j].p >= queries[i].f) { // add in the edges
            //cout << "cur edge: " << edges[j].u << " " << edges[j].v << '\n';
            curAdj[edges[j].u].pb(edges[j].v);
            curAdj[edges[j].v].pb(edges[j].u);
            if (!degCount[edges[j].u]) zeroCount--;
            if (!degCount[edges[j].v]) zeroCount--;
            if (degCount[edges[j].u] == 1) twoCount++;
            if (degCount[edges[j].v] == 1) twoCount++;
            if (degCount[edges[j].u] == 2) twoCount--;
            if (degCount[edges[j].v] == 2) twoCount--;
            degCount[edges[j].u]++;
            degCount[edges[j].v]++;
            if (degCount[edges[j].u] > 2) dfs(edges[j].u);
            if (degCount[edges[j].v] > 2) dfs(edges[j].v);
            if (degCount[edges[j].u] == 2 && degCount[edges[j].v] == 2) {
                if (!marked[edges[j].u] && !marked[edges[j].v]) {
                    if (dfs2(edges[j].u)) {
                        loopCount++;
                        loop[edges[j].u] = 1;
                        //cout << "loop closed" << '\n';
                    }
                }
            }
            edgeCount++;
            j++;
        }
        ans[queries[i].s].f = n-zeroCount-twoCount+loopCount;
        ans[queries[i].s].s = edgeCount-twoCount+loopCount;
        //cout << ans[queries[i].s].f << " " << ans[queries[i].s].s << '\n';
        
    }
    
    F0R(i, q) {
        cout << ans[i].f << " " << ans[i].s << '\n';
    }
    fflush(stdout);
    return 0;
}
