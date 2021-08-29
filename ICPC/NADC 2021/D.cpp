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
const ll MOD = 998244353;
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

const int MX = 4e5+5;
ll a[MX], pref[60][MX];
int n;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    F0R(i, n) cin >> a[i];
    F0R(i, n) a[i+n] = a[i];
    F0R(i, 60) {
        F0R(j, 2*n) {
            pref[i][j+1] = pref[i][j] + ((a[j]&(1LL<<i)) == 0);
        }
    }
    int left[n]; // number of positions to the left such that the interval and-ed is >0
    F0R(i, n) {
        // we want to find j < i such that 
        int lo = 1, hi = n;
        while (lo < hi) {
            int mid = (lo+hi)/2;
            bool ok = 0;
            F0R(j, 60) {
                if (pref[j][i+n+1]-pref[j][i-mid+n] == 0) ok = 1;
            }
            if (ok) lo = mid+1;
            else hi = mid;
        }
        // dbg(i, lo-1);
        left[i] = lo-1;
    }
    int cur = n;
    ll dp[MX]; F0R(i, MX) dp[i] = 0;
    ll sums[MX]; F0R(i, MX) sums[i] = 0;
    dp[0] = 1;
    sums[0] = 0; sums[1] = 1;
    ll curNum = -1;
    ll ans = 0;
    int count = 0;
    while (cur > 0) {
        ll temp = curNum;
        curNum = temp&a[cur];
        // recompute the dp
        if (temp != curNum) {
            // dbg("starting dp at", cur);
            FOR(j, 1, cur) {
                if (j-1-left[j-1]+n > cur && j-1-left[j-1] <= 0) left[j-1] = j-2;
                dp[j] = ((sums[j]-sums[max(j-left[j-1]-1, 0)])%MOD+MOD)%MOD;
                sums[j+1] = (sums[j]+dp[j])%MOD;
                // dbg(j, dp[j], sums[j], sums[max(j-left[j-1]-1, 0)]);
            }
        }
        ans = (ans+dp[cur--])%MOD;
    }
    if (left[0] == n-1) ans = (ans - n+1+MOD)%MOD;
    cout << ans << nl;
    return 0;
}
