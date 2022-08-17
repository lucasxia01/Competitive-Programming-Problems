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

void dbg_out () {cerr << endl;}
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) {
    cerr << H << " "; dbg_out(T...);
}

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int a[n]; F0R(i, n) cin >> a[i];
    stack<int> s1, s2;
    vi v[n][2]; // 0 is greater, 1 is lesser
    F0R(i, n) {
        while (!s1.empty() && a[i] <= a[s1.top()]) { v[s1.top()][0].pb(i); s1.pop(); }
        s1.push(i);
        while (!s2.empty() && a[i] >= a[s2.top()]) { v[s2.top()][1].pb(i); s2.pop(); }
        s2.push(i);
    }
    while (!s1.empty()) s1.pop();
    while (!s2.empty()) s2.pop();
    F0Rd(i, n) {
        while (!s1.empty() && a[i] <= a[s1.top()]) { v[i][0].pb(s1.top()); s1.pop(); }
        s1.push(i);
        while (!s2.empty() && a[i] >= a[s2.top()]) { v[i][1].pb(s2.top()); s2.pop(); }
        s2.push(i);
    }

    int dp[n]; F0R(i, n) dp[i] = i;
    F0R(i, n-1) {
        if (a[i+1] >= a[i]) trav(j, v[i][0]) ckmin(dp[j], dp[i]+1);
        else trav(j, v[i][1]) ckmin(dp[j], dp[i]+1);
    }
    cout << dp[n-1] << nl;
    return 0;
}
