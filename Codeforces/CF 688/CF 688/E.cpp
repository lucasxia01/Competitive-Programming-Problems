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

const int MX = 2e5+5;

vi gr[MX];
int n;
int ans = 0;

int dfs(int v, int p) {
    int ret = 0;
    vi depths;
    trav(u, gr[v])
        if (u != p) {
            int x = dfs(u, v)+1;
//            dbg(v, u, x);
            depths.pb(x);
        }
    if (sz(depths) == 0) return 0;
    if (v == 1) {
        if (sz(depths) == 1) {
            ret = depths[0];
            ckmax(ans, depths[0]);
        } else {
            sort(all(depths), greater<int>());
            ckmax(ans, max(depths[0], depths[1]+1)); // largest and second largest
            ret = depths[0];
        }
    } else {
        if (sz(depths) == 1) {
            ret = depths[0];
        } else {
            sort(all(depths), greater<int>());
            ret = depths[sz(depths)-1];
            ckmax(ans, depths[0]+1); // largest one
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        F0R(i, n+1) gr[i].clear();
        ans = 0;
        int u, v;
        F0R(i, n-1) {
            cin >> u >> v;
            gr[u].pb(v);
            gr[v].pb(u);
        }
        dfs(1, 0);
        cout << ans << nl;
    }
    return 0;
}
