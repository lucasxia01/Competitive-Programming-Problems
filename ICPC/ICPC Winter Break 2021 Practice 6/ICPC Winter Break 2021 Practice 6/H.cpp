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

const int MX = 2005;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    ll H[n+1]; F0R(i, n+1) cin >> H[i];
    while (k--) {
        ld g; cin >> g;
        pair<ld, int> h[n+1]; F0R(i, n+1) { h[i].f = (ld)H[i]-10*i*g; h[i].s = i; }
        ld f[n+1]; F0R(i, n+1) f[i] = h[i].f;
//        F0R(i, n+1) cout << f[i] << " "; cout << nl;
        sort(h, h+(n+1));
        int maxIdx = -1;
        ld ans = -1;
        F0Rd(i, n+1) {
//            dbg(h[i].s, maxIdx);
            if (maxIdx != -1) {
                if (maxIdx > h[i].s) {
                    // try to look further right
                    ld r = maxIdx;
                    if (maxIdx != n) {
                        r += (f[maxIdx]-f[h[i].s])/(f[maxIdx]-f[maxIdx+1]);
                    }
                    ckmax(ans, r-h[i].s);
                }
            }
            ckmax(maxIdx, h[i].s);
        }
        int minIdx = n+1;
        F0R(i, n+1) {
//            dbg(h[i].s, maxIdx);
            if (minIdx != n+1) {
                if (minIdx < h[i].s) {
                    // try to look further right
                    ld l = minIdx;
                    if (minIdx != 0) {
                        l -= (f[h[i].s]-f[minIdx])/(f[minIdx-1]-f[minIdx]);
                    }
                    ckmax(ans, h[i].s-l);
                }
            }
            ckmin(minIdx, h[i].s);
        }
        cout.precision(10);
        if (ans != -1) cout << fixed << ans << nl;
        else cout << "impossible" << nl;
    }
    
    return 0;
}
