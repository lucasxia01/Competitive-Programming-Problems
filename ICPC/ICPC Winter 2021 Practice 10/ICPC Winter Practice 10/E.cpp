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

const int MX = 1<<20;

struct Data {
    int a = 0, b = 0, c = 0, d = 0;
//    Data() {
//        a = b = c = d = 0;
//    }
    Data operator+(const Data& o) const {
        return {a+o.a, b+o.b, c+o.c, d+o.d};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    Data dp[3][n+2];
    dp[0][0] = {1, 0, 0, 0};
    F0R(i, n) {
        // 0
        int x = dp[0][i].a;
        if (x) {
            dp[0][i+1] = dp[0][i+1]+dp[0][i]; dp[0][i+1].b += 2*x; // use two 1x1s
            dp[0][i+1] = dp[0][i+1]+dp[0][i]; dp[0][i+1].c += x; // use a 1x2
            dp[1][i+1] = dp[1][i+1]+dp[0][i]; dp[1][i+1].d += x; // use a tri
            dp[1][i+1] = dp[1][i+1]+dp[0][i]; dp[1][i+1].b += x; dp[1][i+1].c += x; // use a 1x2 and 1x1
            dp[2][i+1] = dp[2][i+1]+dp[0][i]; dp[2][i+1].d += x; // use a tri
            dp[2][i+1] = dp[2][i+1]+dp[0][i]; dp[2][i+1].b += x; dp[2][i+1].c += x; // use a 1x2 and 1x1
            dp[0][i+2] = dp[0][i+2]+dp[0][i]; dp[0][i+2].c += 2*x; // two 2x1s
            dp[0][i+2] = dp[0][i+2]+dp[0][i]+dp[0][i]; dp[0][i+2].b += 2*x; dp[0][i+2].d += 2*x;
            
        }
        // 1
        x = dp[1][i].a;
        if (x) {
            dp[0][i+1] = dp[0][i+1]+dp[1][i]; dp[0][i+1].b += x;
            dp[2][i+1] = dp[2][i+1]+dp[1][i]; dp[2][i+1].c += x;
            dp[0][i+2] = dp[0][i+2]+dp[1][i]; dp[0][i+2].d += x;
        }
        // 2
        x = dp[2][i].a;
        if (x) {
            dp[0][i+1] = dp[0][i+1]+dp[2][i]; dp[0][i+1].b += x;
            dp[1][i+1] = dp[1][i+1]+dp[2][i]; dp[1][i+1].c += x;
            dp[0][i+2] = dp[0][i+2]+dp[2][i]; dp[0][i+2].d += x;
        }
    }
//    F0R(i, n+1) F0R(j, 3) dbg(i, j, dp[j][i].a, dp[j][i].b, dp[j][i].c, dp[j][i].d);
    cout << dp[0][n].a << " " << dp[0][n].b << " " << dp[0][n].c << " " << dp[0][n].d << nl;
    return 0;
}
