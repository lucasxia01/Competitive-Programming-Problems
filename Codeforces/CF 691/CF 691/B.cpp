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

const int MX = 100*100+5;

struct G {
    int a, b;
};
int dp[101][101][MX]; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    G a[n];
    int total = 0;
    F0R(i, n) {
        cin >> a[i].a >> a[i].b;
        total += a[i].b;
    }
    F0R(i, n+1) F0R(j, n+1) F0R(k, MX) dp[i][j][k] = -INF;
    dp[0][0][0] = 0;
    F0R(i, n) {
        F0R(j, n+1) {
            F0R(k, MX) {
                if (dp[i][j][k] == -INF) continue;
                // don't take the current one
                ckmax(dp[i+1][j][k], dp[i][j][k]);
                // take the current one
                if (j == n || k+a[i].a > MX) continue;
                ckmax(dp[i+1][j+1][k+a[i].a], dp[i][j][k]+a[i].b);
            }
        }
    }
    cout.precision(14);
    FOR(j, 1, n) {
        ld ans = 0;
        F0R(k, MX) {
            if (dp[n][j][k] == -INF) continue;
            ckmax(ans, min((ld)k, (ld)(total+dp[n][j][k])/2));
        }
        cout << fixed << ans << " ";
    } cout << nl;
    return 0;
}
