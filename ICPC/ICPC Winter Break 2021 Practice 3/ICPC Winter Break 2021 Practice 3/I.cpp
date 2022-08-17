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

const int MX = 105;

int par[MX], sz[MX];
int find(int i) {
    return (par[i]==i?i:par[i]=find(par[i]));
}
bool merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a;
    sz[a] += sz[b];
    return true;
}

vi gr[MX];
bool vis[MX];
bool off[MX];
int dp[MX][2];

void dfs(int v) {
    if (vis[v]) return;
    vis[v] = 1;
    dp[v][1] = 1;
    dp[v][0] = 0;
    trav(u, gr[v]) {
        if (!vis[u]) {
            dfs(u);
            dp[v][1] += dp[u][0];
            dp[v][0] += max(dp[u][0], dp[u][1]);
        }
    }
    if (off[v]) dp[v][1] = -INF;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    F0R(i, n) par[i] = i;
    F0R(i, n) sz[i] = 1;
    int a, b;
    int cnt = 0;
    int extra[m][2];
    F0R(i, m) {
        cin >> a >> b;
        a--; b--;
        if (!merge(a, b)) {
            extra[cnt][0] = a;
            extra[cnt][1] = b;
            cnt++;
        } else {
            gr[a].pb(b);
            gr[b].pb(a);
        }
    }
    int ans = 0;
    F0R(i, 1<<cnt) {
        memset(vis, 0, sizeof vis);
        F0R(j, n) dp[j][0]=dp[j][1]=0;
        F0R(j, cnt) {
            off[extra[j][(i&(1<<j))==0]] = 1;
        }
        int temp = 0;
        F0R(j, n) {
            if (!vis[j]) {
                dfs(j);
                temp += max(dp[j][0], dp[j][1]);
            }
        }
        
        F0R(j, cnt) {
            off[extra[j][0]] = off[extra[j][1]] = 0;
        }
        ckmax(ans, temp);
    }
    cout << ans << nl;
    return 0;
}
