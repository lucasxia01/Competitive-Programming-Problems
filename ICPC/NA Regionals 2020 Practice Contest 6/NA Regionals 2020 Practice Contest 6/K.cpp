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
#include <climits>

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

const int MX = 4e5+5;

struct P {
    int x, y, i;
    bool operator<(const P& o) const {
        return tie(x, y, i) < tie(o.x, o.y, o.i);
    }
};

map<pi, int> s;
int n, m, b;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int dirs[MX];
vi gr[MX];
vpi h[MX];
vpi v[MX];

void dfs(int x, int y, int i, int p) {
    F0R(d, 4) {
        int nx = x+dx[d], ny = y+dy[d];
        if (s.find({nx, ny}) != s.end()) {
            int idx = s[{nx, ny}];
            if (idx == p) continue;
            dirs[idx] = d;
            gr[i].pb(idx);
            dfs(nx, ny, idx, i);
        }
    }
}

vi order;
void topsort() {
    int inCnt[b]; F0R(i, b) inCnt[i] = 0;
    F0R(i, b) trav(a, gr[i]) inCnt[a]++;
    vi roots;
    F0R(i, b) if (inCnt[i] == 0) roots.pb(i);
    while (!roots.empty()) {
        int cur = roots.back(); roots.pop_back();
        order.pb(cur);
        trav(u, gr[cur]) {
            inCnt[u]--;
            if (inCnt[u] == 0) roots.pb(u);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> b;
    pi blocks[b];
    F0R(i, b) {
        int r, c; cin >> r >> c;
        s.insert({{r, c}, i});
        h[c].pb({r, i});
        v[r].pb({c, i});
        blocks[i] = {r, c};
    }
    dfs(blocks[0].f, blocks[0].s, 0, -1);
    FOR(i, 1, m) sort(all(h[i]));
    FOR(i, 1, n) sort(all(v[i]));
    
    // now go through each direction and add the edges
    // dir 1
    int cur = -1;
    FOR(i, 1, n) {
        cur = -1;
        trav(a, v[i]) {
            if (cur != -1) gr[cur].pb(a.s);
            if (dirs[a.s] == 0) cur = a.s;
        }
    }
    FOR(i, 1, n) {
        cur = -1;
        reverse(all(v[i]));
        trav(a, v[i]) {
            if (cur != -1) gr[cur].pb(a.s);
            if (dirs[a.s] == 2) cur = a.s;
        }
    }
    
    FOR(i, 1, m) {
        cur = -1;
        trav(a, h[i]) {
            if (cur != -1) gr[cur].pb(a.s);
            if (dirs[a.s] == 1) cur = a.s;
        }
    }
    FOR(i, 1, m) {
        cur = -1;
        reverse(all(h[i]));
        trav(a, h[i]) {
            if (cur != -1) gr[cur].pb(a.s);
            if (dirs[a.s] == 3) cur = a.s;
        }
    }
    topsort();
    if (sz(order) != b) {
        cout << "impossible" << nl;
        return 0;
    }
    cout << "possible" << nl;
    order.erase(order.begin());
    trav(a, order) {
        if (dirs[a] == 0) cout << "< " << blocks[a].f << nl;
        if (dirs[a] == 2) cout << "> " << blocks[a].f << nl;
        if (dirs[a] == 1) cout << "^ " << blocks[a].s << nl;
        if (dirs[a] == 3) cout << "v " << blocks[a].s << nl;
    }
    return 0;
}
