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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    vi p; bool isNotPrime[MX] = {};
    FOR(i, 2, MX-1) {
        if (!isNotPrime[i]) {
            p.pb(i);
            for (int j = 2*i; j < MX; j+=i) isNotPrime[j] = 1;
        }
    }
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int a[n]; F0R(i, n) cin >> a[i];
        F0R(i, n) trav(u, p) while (a[i]%(u*u) == 0) a[i] /= (u*u);
        unordered_map<int, int> f;
        F0R(i, n) f[a[i]]++;
        int ans0 = -1, ans = -1;
        int total = 0;
        trav(u, f) {
            ckmax(ans0, u.s);
            if (u.f == 1) total += u.s;
            else if (u.s&1) ckmax(ans, u.s);
            else total += u.s;
        }
        ckmax(ans, total);
        int q; cin >> q;
        F0R(i, q) {
            ll w; cin >> w;
            if (w == 0) cout << ans0 << nl;
            else cout << ans << nl;
        }
    }
    return 0;
}
