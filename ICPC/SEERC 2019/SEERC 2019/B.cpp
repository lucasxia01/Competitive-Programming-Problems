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
const ll INF = 1LL<<50;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Quest {
    int x, y; ll t, r;
    bool operator<(const Quest& o) const {
        return (x < o.x);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, s1, s2; cin >> n >> s1 >> s2;
    Quest q[n];
    F0R(i, n) cin >> q[i].x >> q[i].t >> q[i].y >> q[i].r;
    sort(q, q+n);
    ll dp[2][s1+1][s2+1]; F0R(i, 2) F0R(j, s1+1) F0R(k, s2+1) dp[i][j][k] = INF;
    dp[0][0][0] = 0;
    F0R(i, n) {
        int nxt = (i&1)^1, cur = i&1;
        F0R(j, s1+1) F0R(k, s2+1) {
            ckmin(dp[nxt][j][k], dp[cur][j][k]);
            if (j < s1) ckmin(dp[nxt][min(j+q[i].x,s1)][min(k+max(0,j+q[i].x-s1),s2)],  dp[cur][j][k]+q[i].t);
            if (k < s2) ckmin(dp[nxt][j][min(s2,k+q[i].y)], dp[cur][j][k]+q[i].r);
        }
    }
    if (dp[n&1][s1][s2] == INF) cout << -1 << nl;
    else cout << dp[n&1][s1][s2] << nl;
    return 0;
}
