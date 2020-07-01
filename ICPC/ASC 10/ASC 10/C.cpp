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
const ll INF = (1LL<<50) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("codes.in", "r", stdin);
//    freopen("codes.out", "w", stdout);
    int n; cin >> n;
    string ans[n]; F0R(i, n) ans[i] = "";
    vector<pair<ll, pi> > a;
    F0R(i, n) {
        ll x; cin >> x;
        a.pb({x, {i, i}});
    }
    F0R(t, n-1) {
        ll s = INF, sIdx = -1;
        F0R(i, sz(a)-1) {
            if (ckmin(s, a[i].f + a[i+1].f)) sIdx = i;
        }
        a[sIdx].f += a[sIdx+1].f;
        FOR(i, a[sIdx].s.f, a[sIdx].s.s) ans[i] += '0';
        FOR(i, a[sIdx+1].s.f, a[sIdx+1].s.s) ans[i] += '1';
        a[sIdx].s.s = a[sIdx+1].s.s;
        a.erase(a.begin()+sIdx+1);
    }
    F0R(i, n) {
        reverse(ans[i].begin(), ans[i].end());
        cout << ans[i] << nl;
    }
    return 0;
}
