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

const int MX = 1000;
complex<ld> a[MX], b[MX];
complex<ld> r[9], r2[9];

complex<ld> rot(complex<ld> c, int k) {
    while (arg(c) > 2*PI/k || arg(c) < 0) {
        // dbg(c.real(), c.imag(), arg(c)/(PI)*180)
        c *= r[k];
    }
    c *= r2[k];
    // dbg();
    return c;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    F0R(i, n) {ld x, y; cin >> x >> y; a[i] = {x, y}; }
    F0R(i, 9) r[i] = {cosl(PI/i*2), sinl(PI/i*2)};
    F0R(i, 9) r2[i] = {cosl(-PI/i), sinl(-PI/i)};
    int ans = -1; ld hi = 0;
    FOR(i, 3, 8) {
        F0R(j, n) b[j] = rot(a[j], i);
        ld M = -INF, m = INF;
        F0R(j, n) {
            ckmax(M, b[j].real());
            ckmin(m, b[j].real());
        }
        if (ckmax(hi, m/M)) ans = i;
    }
    cout << ans << " ";
    cout.precision(10);
    cout << fixed << hi*hi << nl;
    return 0;
}