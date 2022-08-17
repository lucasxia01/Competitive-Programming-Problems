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

const char nl = '\n';
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

struct State {
    ld e;
    int t, i;
    bool operator<(const State& o) const{
        return (e > o.e);
    }
};

const int MX = 5005;
const int MXN = 505;
const int MXT = 10005;
int n, m;
vi edges[MX];
ld p[MXT][MXN];
ld vis[MXT][MXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    int u, v;
    F0R(i, m) {
        cin >> u >> v;
        edges[u].pb(v);
        edges[v].pb(u);
    }
    int P;
    cin >> P;
    F0R(i, P) {
        cin >> v;
        p[0][v] = 1;
    }
    F0R(i, MXT) F0R(j, MXN) vis[i][j] = INF;
    vis[0][0] = 0;
    FOR(i, 0, MXT-2) {
        F0R(j, n) {
            int SZ = sz(edges[j]);
            trav(a, edges[j]) {
                p[i+1][a] += p[i][j]/SZ;
            }
        }
    }
    priority_queue<State> q;
    q.push({0, 0, 0});
    cout.precision(10);

    while (!q.empty()) {
        auto [e, t, i] = q.top(); q.pop();
        // cout << i << " " << t << " " << e << nl;
        if (i == n-1) {
            cout << fixed << e << nl;
            return 0;
        }
        trav(a, edges[i]) {
            if (ckmin(vis[t+1][a], e+p[t+1][a]))
                q.push({e+p[t+1][a], t+1, a});
        }
    }
    assert(0);
    return 0;
}
