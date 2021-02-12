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

const int MX = 1200;
struct P {
    ll x, y;
};
P a[MX];
int vis[MX];
ld mid;
int n;

ll dist(P b, P c) {
    return (b.x-c.x)*(b.x-c.x)+(b.y-c.y)*(b.y-c.y);
}
bool dfs(int v, int m) {
    vis[v] = m;
//    cout << "cur " << mid << " " << v << ' ' << m << nl;
    F0R(i, n) {
        if (i == v || dist(a[v], a[i]) >= mid) continue;
//        cout << i << " " << v << " " << dist(a[v], a[i]) << nl;
        if (!vis[i]) {if (!dfs(i, 3-m)) return 0;}
        else if (vis[i] == m) return 0;
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("radio.in", "r", stdin);
//    freopen("radio.out", "w", stdout);
    cin >> n;
    F0R(i, n) cin >> a[i].x >> a[i].y;
    ll lo = 0, hi = (ll)1e10;
    while (lo < hi) {
        mid = (lo+hi)/2;
        memset(vis, 0, sizeof vis);
        bool ok = 1;
        F0R(i, n) if (!vis[i]) if (!dfs(i, 1)) { ok = 0; break; }
        if (ok) lo = mid+1;
        else hi = mid;
    }
    mid = (lo+hi)/2 - 1;
    memset(vis, 0, sizeof vis);
    F0R(i, n) if (!vis[i]) dfs(i, 1);
    cout.precision(12);
    cout << fixed << sqrtl(mid)/2 << nl;
    F0R(i, n) if (vis[i]) cout << vis[i] << " "; else cout << 1 << " "; cout<<nl;
    return 0;
}
