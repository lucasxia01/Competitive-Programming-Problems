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
const ll MOD = 998244353;
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3011;
string s, t;
ll dp[MX][MX], vis[MX][MX];
int n, m;

ll solve(int preBuilt, int ptrS) {
    if (vis[preBuilt][ptrS]) return dp[preBuilt][ptrS];
    ll ret;
    if (ptrS < preBuilt) ret = 0;
    else if (ptrS >= n) ret = (preBuilt == m);
    else if (preBuilt == m) ret = 1+solve(preBuilt, ptrS+1);
    else {
        ret = solve(preBuilt, ptrS+1) + solve(0, ptrS+1);
        if (s[ptrS] == t[preBuilt]) ret = (ret+solve(preBuilt+1, ptrS+1))%MOD;
    }
    dp[preBuilt][ptrS] = ret;
    vis[preBuilt][ptrS] = 1;
    cout << preBuilt << " " << ptrS << " " << ret << endl;
    return ret;
}

ll simulate(int a, int b) {
    int total = b-a+1;
    if (b == m-1) return dp[m-a][total];
    ll ret = 0;
    if (a != 0 && s[total] == t[a-1]) ret = (ret+simulate(a-1, b))%MOD;
    if (s[total] == t[b+1]) ret = (ret+simulate(a, b+1))%MOD;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> s >> t;
    n = (int)s.length(); m = (int)t.length();
    ll ans = 0;
    reverse(t.begin(), t.end());
    solve(0, 0);
    reverse(t.begin(), t.end());
    F0R(i, m+1) {
        cout << i << " " << simulate(i, i-1) << endl;
        ans = (ans+simulate(i, i-1))%MOD;
    }
    cout << ans << endl;
    return 0;
}
