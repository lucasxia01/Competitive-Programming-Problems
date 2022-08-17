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

const int MX = 1005;

int par[MX];
int sz[MX];

int find_set(int v) {
    if (v == par[v])
        return v;
    return par[v] = find_set(par[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b])
            swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    int a[n]; F0R(i, n) cin >> a[i];
    F0R(i, n) par[i+1] = i+1;
    F0R(i, n) sz[i+1] = 1;
    F0R(i, n) union_sets(i+1, a[i]);
    vpi v;
    int vis[n+1]; F0R(i, n+1) vis[i] = -1;
    F0R(i, n) if (par[i+1] == i+1) {
        // we want to dfs in this component
        int cur = i+1;
        int cnt = 0;
        int cycleSize = 1;
        while (1) {
            if (vis[cur] != -1) {
                cycleSize = cnt-vis[cur];
                break;
            }
            vis[cur] = cnt++;
            cur = a[cur-1];
        }
        v.pb({cycleSize, sz[i+1]});
    }
    int m = sz(v);
    bool dp[m+1][k+1];
    F0R(i, m+1) F0R(j, k+1) dp[i][j] = 0;
    dp[0][0] = 1;
    F0R(i, m) {
        F0R(j, k+1) {
            if (!dp[i][j]) continue;
            dp[i+1][j] = 1;
            FOR(jj, v[i].f, v[i].s) if (j+jj <= k) dp[i+1][j+jj] = 1;
        }
    }
    F0Rd(i, k+1) if (dp[m][i]) {
        cout << i << nl;
        return 0;
    }
    return 0;
}
