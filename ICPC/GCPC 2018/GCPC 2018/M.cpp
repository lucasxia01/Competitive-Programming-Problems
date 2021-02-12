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
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 500*500, MXQ = 1e5+5;
int m, n, q;
int h[500][500];
vector<pair<int, pi> > f;
int par[MX];
unordered_set<int> s[MX];
int ans[MXQ];

int find(int v) {
    return (par[v] == v ? v : par[v] = find(par[v]));
}

void merge(int a, int b, int val) {
    a = find(a); b = find(b);
    if (a != b) {
        if (sz(s[a]) < sz(s[b])) swap(a, b);
        trav(u, s[b]) { // go through smaller set
            if (s[a].count(u)) {
                s[a].erase(u);
                ans[u] = val;
            } else s[a].insert(u);
        }
        par[b] = a;
    }
}

int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> m >> n >> q;
    F0R(i, q) ans[i] = INF;
    
    F0R(i, m) F0R(j, n) {
        cin >> h[i][j];
        f.pb({h[i][j], {i, j}});
    }
    sort(all(f));
    F0R(i, q) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        x1--; y1--; x2--; y2--;
        int p1 = x1*n+y1, p2 = x2*n+y2;
        if (p1 == p2) ans[i] = h[x1][y1];
        s[p1].insert(i);
        s[p2].insert(i);
    }
    F0R(i, MX) par[i] = i;
    trav(g, f) {
        pi p = g.s;
        F0R(d, 4) {
            int nx = p.f+dx[d], ny = p.s+dy[d];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            if (g.f >= h[nx][ny]) merge(p.f*n+p.s, nx*n+ny, g.f);
        }
    }
    F0R(i, q) cout << ans[i] << nl;
    return 0;
}
