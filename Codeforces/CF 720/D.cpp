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

const int MX = 1e5+5;

vi gr[MX];
int dp[MX][2]; // 0 is can use it, 1 is can't use
vi par[MX][2];

void dfs(int v, int p) {
    int total = 0;
    vpi a;
    trav(u, gr[v]) {
        if (u == p) continue;
        dfs(u, v);
        dp[v][0] += max(dp[u][0], dp[u][1]);
        total += max(dp[u][0], dp[u][1]);
        a.pb({max(dp[u][0], dp[u][1])-dp[u][0], u});
    }
    sort(all(a));
    if (sz(a) >= 1) {
        if (ckmax(dp[v][0], total-a[0].f+1)) {
            
        }
    }
    if (sz(a) >= 2) {
        ckmax(dp[v][1], total-a[0].f-a[1].f+2);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        F0R(i, n+1) gr[i].clear();
        F0R(i, n+1) dp[i][0] = dp[i][1] = 0;
        F0R(i, n-1) {
            int a, b; cin >> a >> b;
            gr[a].pb(b);
            gr[b].pb(a);
        }
        dfs(1, 0);
        cout << n-1-max(dp[1][0], dp[1][1]) << nl;
    }
    
    return 0;
}
