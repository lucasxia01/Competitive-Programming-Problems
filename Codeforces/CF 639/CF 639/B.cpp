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
const int MX = 1005;
int n, m;
string g[MX];
bool vis[MX][MX];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || vis[x][y] || g[x][y] == '.') return;
    vis[x][y] = 1;
    F0R(d, 4) dfs(x+dx[d], y+dy[d]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    F0R(i, n) cin >> g[i];
//    bool r[n], c[m];
//    F0R(i, n) r[i] = 1; F0R(i, m) c[i] = 1;
    int blackCount = 0;
    F0R(i, n) F0R(j, m) {
        if (g[i][j] == '#') blackCount++;
    }
    if (blackCount == 0) {
        cout << 0 << nl;
        return 0;
    }
    bool ok = true;
    bool empty1 = 0, empty2 = 0;
    F0R(i, n) {
        int lo = m, hi = -1;
        F0R(j, m) {
            if (g[i][j] == '#') {
                ckmin(lo, j);
                ckmax(hi, j);
            }
        }
        if (lo > hi) empty1 = 1;
        FOR(j, lo, hi-1) {
            if (g[i][j] == '.') ok = false;
        }
    }
    F0R(j, m) {
        int lo = n, hi = -1;
        F0R(i, n) {
            if (g[i][j] == '#') {
                ckmin(lo, i);
                ckmax(hi, i);
            }
        }
        if (lo > hi) empty2 = 1;
        FOR(i, lo, hi-1) {
            if (g[i][j] == '.') ok = false;
        }
    }
    if (!ok || (empty1^empty2)) {
        cout << -1 << nl;
        return 0;
    }
    int ans = 0;
    F0R(i, n) F0R(j, m) {
        if (g[i][j] == '#' && !vis[i][j]) {
            ans++;
            dfs(i, j);

        }
    }
    cout << ans << nl;

    return 0;
}
