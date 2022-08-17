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

const int MX = 1e6;
int dp[MX] = {};
vl primes;

int solve(int x) {
    if (x <= 1) return 0;
    if (dp[x]) return dp[x];
    trav(p, primes) {
        if (p*p > x) break;
        if (x%p == 0) {
            ckmax(dp[x], 1+solve(x/p-1));
            ckmax(dp[x], 1+solve(p-1));
            ckmax(dp[x], solve(x/p));
            ckmax(dp[x], solve(p));
        }
    }
    ckmax(dp[x], 1);
    // dbg(x, dp[x]);
    return dp[x];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    vector<char> is_prime(MX+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= MX; i++) {
        if (is_prime[i]) {
            primes.pb(i);
            for (int j = i * i; j <= MX; j += i)
                is_prime[j] = false;
        }
    }
    
    F0R(tt, t) {
        int n; cin >> n;
        int ans = 1;
        int x = n;
        trav(p, primes) {
            if (p*p > x) break;
            if (x%p == 0) {
                if (p != 2) {
                    ckmax(ans, 1+solve(x/p-1));
                    ckmax(ans, 1+solve(p-1));
                }
                ckmax(ans, solve(x/p));
                ckmax(ans, solve(p));
            }
        }
        cout << "Case #" << tt+1 << ": " << ans << nl;
    }
    return 0;
}
