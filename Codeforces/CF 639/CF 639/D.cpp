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
const ll INF = (1LL<<61)+(1LL<<60);
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MX = 1e5+5;
ll a[MX];
ll ans[MX];
int n; ll k;

ll check(ll b) {
    ll total = 0;
    F0R(i, n) {
        ll C = b+1-a[i];
        if (C > 0) {
            ans[i] = 0;
            continue;
        }
        ll root = (ll)((ld)-0.5 + sqrtl((ld)1.0/4-(ld)C/3)); // directly calculate how much based on the bound of minimum change of adding 1
        assert(root >= 0);
        ans[i] = min(root+1, a[i]);
        total += min(root+1, a[i]);
        if (total > k) return total;
    }
    return total;
}

int main() {
    
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    F0R(i, n) cin >> a[i];
    ll lo = -INF, hi = INF;
    ll ret = 0;
    while (lo < hi) { // because of monotonicity of the change of value, we can binary search for when we stop
        ll mid = (lo+hi)/2;
        if (lo+hi < 0) mid = (lo+hi-1)/2;
        assert(mid >= lo && mid <= hi && lo >= -INF && hi <= INF);
        ret = check(mid);
        if (ret > k) lo = mid+1;
        else if (ret < k) hi = mid;
        else break;
    }
    
    ll cur = (lo+hi)/2;
    ret = check(cur);
    if (ret > k) {
        cur++;
        ret = check(cur);
    }
    ll b[n];
    F0R(i, n) b[i] = ans[i];
    assert (ret <= k && check(cur-1) >= k);
    ll diff = k - ret;
    F0R(i, n) {
        if (diff == 0) break;
        if (b[i] < ans[i]) {
            assert(b[i]+1 == ans[i]);
            b[i]++;
            diff--;
        } else assert(b[i] == ans[i]);
    }
    F0R(i, n) cout << b[i] << " "; cout << nl;
    return 0;
}
