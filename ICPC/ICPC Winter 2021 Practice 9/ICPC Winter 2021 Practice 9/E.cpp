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

typedef pair<int, int> pii;
typedef pair<ll,ll> pl;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpi;
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
const ll MOD = 1000000009; // 998244353
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

ll binpow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

ll inv(ll x) {
    return binpow(x, MOD-2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int a[n]; F0R(i, n) cin >> a[i];
    // compress
    map<int, int> m; F0R(i, n) m[a[i]] = 0;
    int cnt = 0;
    trav(v, m) m[v.f] = cnt++;
    F0R(i, n) a[i] = m[a[i]];
    sort(a, a+n);
    int cnts[cnt][n+1]; F0R(i, cnt) cnts[i][0] = 0; // prefix sums
    F0R(i, cnt) F0R(j, n) cnts[i][j+1] = cnts[i][j] + (a[j]==i);
    ll dp[n+1]; dp[0] = 1;
    ll perm[n+1]; F0R(i, n+1) perm[i] = 1;
    FOR(i, 1, n) {
        dp[i] = 0;
        F0R(j, i) perm[j] = ((perm[j]*(i-j))%MOD * inv(cnts[a[i-1]][i]-cnts[a[i-1]][j]))%MOD;
        FOR(j, 1, i) dp[i] = ((dp[j-1]*perm[j])%MOD+dp[i])%MOD;
        dp[i] = ((perm[0]-dp[i])%MOD+MOD)%MOD;
    }
    cout << dp[n] << nl;
    return 0;
}
