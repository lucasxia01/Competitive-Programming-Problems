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

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m, u, v;
        cin >> n;
        pl p[n];
        F0R(i, n) cin >> p[i].f >> p[i].s;
        cin >> m;
        vl edges[n];
        F0R(i, m) {
            cin >> u >> v;
            u--; v--;
            edges[u].pb(v);
            edges[v].pb(u);
        }
        ld dist[n][n];
        F0R(i, n) F0R(j, n) {
            dist[i][j] = sqrt((ld)(p[i].f-p[j].f)*(p[i].f-p[j].f) + (ld)(p[i].s-p[j].s)*(p[i].s-p[j].s));
        }
        ld dp[n+1][n+1][2]; // states are current node, other node of the segment, direction
        F0R(k, n) { // k is number of nodes in the segment
            F0R(i, n) { // i is current node
                for (int cw = 0; cw < 2; cw++) { // if its clockwise or not
                    // second state is then fixed
                    int c = (1-cw*2); // -1 if cw, 1 if ccw
                    int b = (i + c*k+n)%n;
                    dp[i][b][cw] = 0;
                    trav(j, edges[i]) {
                        if (cw&1) { // if its in between i, i-1, ..., b+1, b
                            if ((i >= b && (i >= j && j >= b))
                                || (i < b && (j <= i || j >= b))) {
                                ld temp = max(dp[j][b][cw], dp[j][(i+c+n)%n][cw^1]) + dist[i][j];
                                dp[i][b][cw] = max(dp[i][b][cw], temp);
                            }
                        } else { // if its in between i, i+1, ..., b-1, b
                            if ((i <= b && (i <= j && j <= b))
                            || (i > b && (j >= i || j <= b))) {
                                ld temp = max(dp[j][b][cw], dp[j][(i+c)%n][cw^1]) + dist[i][j];
                                dp[i][b][cw] = max(dp[i][b][cw], temp);
                            }
                        }
                    }
                }
            }
        }
        ld ans = 0;
        F0R(i, n) {
            ans = max(ans, dp[i][(i+n-1)%n][0]);
            assert(dp[i][(i+n-1)%n][0] == dp[i][(i+1)%n][1]);
        }
        cout.precision(10);
        cout << fixed <<  ans << '\n';
    }
    return 0;
}
