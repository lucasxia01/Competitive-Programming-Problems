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

const int MX = 1e5+5;
vi e[MX];
ll p[MX], h[MX];
int n, m;

pl dfs(int v, int par) {
    pl c = {0, 0};
    trav(u, e[v]) {
        if (u != par) {
            pi ret = dfs(u, v);
//            cout << u+1 << " " << ret.f << " " << ret.s << nl;
            if (ret.f == -1) return {-1, -1};
            c.f += ret.f; c.s += ret.s;
        }
    }
    ll total = c.f + c.s + p[v];
    if (c.f-c.s-p[v] <= h[v] && total >= h[v] && !((total+h[v])%2)) return {(total+h[v])/2,(total-h[v])/2};
    return {-1, -1};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        F0R(i, n) cin >> p[i];
        F0R(i, n) cin >> h[i];
        int u, v;
        F0R(i, MX) e[i].clear();
        F0R(i, n-1) {
            cin >> u >> v;
            u--; v--;
            e[u].pb(v);
            e[v].pb(u);
        }
        pi ret = dfs(0, -1);
        if (ret.f == -1) cout << "NO" << nl;
        else cout << "YES" << nl;
    }
    return 0;
}
