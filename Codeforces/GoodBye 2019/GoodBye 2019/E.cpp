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

const int MX = 10;

struct P {
    ll x, y;
    ll dist(P o) { return (x-o.x)*(x-o.x)+(y-o.y)*(y-o.y);}
};

vi edges[MX];
int vis[MX];
int color[MX];
void dfs(int v, int c, bool diff) {
    vis[v] = 1;
    cout << v << " " << c << nl;
    color[v] = c;
    trav(u, edges[v]) {
        if (!vis[u]) dfs(u, c^diff, diff);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    P p[n];
    F0R(i, n) cin >> p[i].x >> p[i].y;
    F0R(i, n) color[i] = -1;
    map<ll, vector<pi> > m;
    F0R(i, n) F0R(j, i) {
        m[p[i].dist(p[j])].pb({i, j});
    }
    trav(a, m) {
        cout << a.f << nl;
        set<int> ps;
        set<int> colored;
        bool diff = 1;
        trav(e, a.s) {
            edges[e.f].pb(e.s);
            edges[e.s].pb(e.f);
            if (color[e.f] != -1 && color[e.s] != -1)
                if (color[e.f] == color[e.s]) diff = 0;
            ps.insert(e.f);
            ps.insert(e.s);
            if (color[e.f] != -1) colored.insert(e.f);
            if (color[e.s] != -1) colored.insert(e.s);
        }
        cout << diff << nl;
        trav(v, colored) {
            dfs(v, color[v], diff);
            cout << nl;
        }
        trav(v, ps) {
            if (!vis[v] && color[v] == -1) dfs(v, 1, diff);
        }
        trav(e, a.s) {
            edges[e.f].clear();
            edges[e.s].clear();
        }
        trav(v, ps) vis[v] = 0;
    }
    int ans = 0;
    F0R(i, n) ans += color[i];
    assert(ans != 0 && ans != n);
    cout << ans << nl;
    F0R(i, n) {
        assert(color[i] != -1);
        if (color[i]) cout << i+1 << " ";
    }
    return 0;
}
