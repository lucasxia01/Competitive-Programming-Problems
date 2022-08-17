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

const int MX = 1e6, MXN = 500;
struct State {
    int h, x, y;
    bool operator>(const State& o) const {
        return tie(h, x, y) > tie(o.h, o.x, o.y);
    }
};

priority_queue<State, vector<State>, greater<State> > pq;
int a[MXN][MXN];
int vis[MXN][MXN];
int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1}, dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int n, m;

void dfs(int sX, int sY) {
    vis[sX][sY] = a[sX][sY];
    pq.push({a[sX][sY], sX, sY});
    while (!pq.empty()) {
        State cur = pq.top(); pq.pop();
//        dbg(cur.h, cur.x, cur.y);
        F0R(d, 8) {
            int nx = cur.x+dx[d], ny = cur.y+dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || vis[nx][ny] || a[nx][ny] >= 0) continue;
            vis[nx][ny] = max(cur.h, a[nx][ny]);
            pq.push({vis[nx][ny], nx, ny});
        }
    }

}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    F0R(i, n) F0R(j, m) cin >> a[i][j];
    int sX, sY; cin >> sX >> sY; sX--; sY--;
    dfs(sX, sY);
    ll ans = 0;
    F0R(i, n) F0R(j, m) {
        ans += -vis[i][j];
    }
    cout << ans << nl;
    return 0;
}
