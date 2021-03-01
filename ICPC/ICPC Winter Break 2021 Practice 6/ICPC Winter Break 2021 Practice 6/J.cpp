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
const ll INF = (1LL<<50) + 123;
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

const int MX = 5e5+5;
int n; 
ll C, R; 
ll a[MX]; 
pi ptrs[MX];
ll cur = 0;

int check(int dist, ll x, ll y) {
    if ((x*y > 0 && dist%2==0) || (x*y < 0 && dist%2==1)) {
        return 0;
    } else {
        return 1;
    }
}

void remove(int idx, int l, int r) {
    if (a[idx] == 0) {
        if (l != -1) ptrs[l].s = r;
        if (r != n) ptrs[r].f = l;
        return;
    }
    if (l != -1) {
        cur -= R*check(idx-l, a[l], a[idx]);
        ptrs[l].s = r;
    }
    if (r != n) {
        cur -= R*check(r-idx, a[idx], a[r]);
        ptrs[r].f = l;
    }
    if (l != -1 && r != n) {
        cur += R*check(r-l, a[l], a[r]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> C >> R;
    F0R(i, n) cin >> a[i];
    F0R(i, n) {
        ptrs[i].f = i-1; ptrs[i].s = i+1;
    }
    pl vals[n]; F0R(i, n) vals[i] = {abs(a[i]), i};
    sort(vals, vals+n);
    vi v; F0R(i, n) if (a[i] != 0) v.pb(a[i]); else cur += R;
    F0R(i, sz(v)-1) cur += R*check(1, v[i], v[i+1]);
    ll ans = cur;
    // dbg(cur);
    F0R(i, n) if (a[i] == 0) remove(i, ptrs[i].f, ptrs[i].s);
    cur = 0;
    F0R(i, n) {
        if (a[i] == 0) continue;
        int r = ptrs[i].s;
        if (r == n) break;
        cur += R*check(r-i, a[i], a[r]);
    }
    // dbg(cur);
    F0R(i, n) { // deal with 0s before this please
        int idx = vals[i].s;
        if (a[idx] != 0) {
            int l = ptrs[idx].f, r = ptrs[idx].s;
            remove(idx, l, r);
            // dbg(vals[i].f, cur, l, idx, r);
        }
        if (i == n-1 || vals[i+1].f != vals[i].f) {
            // dbg(cur, vals[i].f+1);
            ckmin(ans, cur+(vals[i].f+1)*C);
        }
    }

    cout << ans << nl;
    return 0;
}
