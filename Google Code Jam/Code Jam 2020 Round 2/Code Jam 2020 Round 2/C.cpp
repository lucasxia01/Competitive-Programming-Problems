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
const int INF = 1e5;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

void solve() {
    int n; cin >> n;
    vpi h; int x, y;
    F0R(i, n) {
        cin >> x >> y;
        h.pb(mp(x, y));
    }
    int a[n]; F0R(i, n) a[i] = i;
    int ans = 1;
    do {
        // 0 with 1, 2 with 3, 4 with 5, 6 by itself
        F0R(i, n) { // starting point
            if ((i^1) >= n) continue; // no pair
            ckmax(ans, 2);
            F0R(j, n) { // second point
                int o = i^1;
                if (j == i || j == o) continue;
                int cur = 3;
                int vis[7] = {};
                ll x = h[i].f + h[o].f - h[j].f;
                ll y = h[i].s + h[o].s - h[j].s;
                ll cx = h[j].f, cy = h[j].s;
                vis[i] = vis[o] = vis[j] = 1;
                while (1) {
                    bool ok = false;
                    F0R(k, n) {
                        ll dx = h[k].f - cx;
                        ll dy = h[k].s - cy;
                        if (!vis[k] && dy*(h[o].f - h[j].f) == dx*(h[o].s - h[j].s)) {
                            cur++;
                            cx = h[k].f; cy = h[k].s;
                            ok = true;
                            vis[k] = 1;
                            break;
                        }
                    }
                    if (!ok) break;
                }
                
                ckmax(ans, cur);
            }
        }
    } while (next_permutation(a, a+n));
    cout << ans << nl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    F0R(i, t) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    
    return 0;
}
