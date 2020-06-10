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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 63e6;

ll gcd(ll a, ll b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a%b);
}

ll c, n, p;
pl sh[505];
pl pack[50005];
ll dp[MX];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> c >> n >> p;
    F0R(i, n) cin >> sh[i].f >> sh[i].s;
    int N = 0;
    F0R(i, p) {
        int m; cin >> m;
        ll total = 0, prof = 0;
        F0R(j, m) {
            ll id, q;
            cin >> id >> q; id--;
            total += sh[id].f*q;
            prof += (sh[id].s-sh[id].f)*q;
        }
        if (total > c || prof <= 0) continue;
        pack[++N] = {total, prof};
    }
    ll g = 0;
    FOR(i, 1, N) g = gcd(g, pack[i].f);
    assert(g);
    FOR(i, 1, N) pack[i].f /= g;
    c/=g;
    assert(c <= MX);
    ll sum = 0;
    FOR(i, 1, N) {
        cout << pack[i].f << " " << pack[i].s << nl;
        sum += pack[i].f;
        for (ll j = min(sum, c); j >= pack[i].f; j--) dp[j] = max(dp[j], dp[j-pack[i].f]+pack[i].s);
    }
    cout << dp[min(c, sum)] << nl;
    return 0;
}
