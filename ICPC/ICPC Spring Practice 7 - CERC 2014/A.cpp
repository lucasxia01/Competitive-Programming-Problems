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

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        ll W = 0, B = 0;
        vector<pair<ll, char> > v;
        F0R(i, n) {
            ll k; char c; cin >> k >> c;
            if (c == 'W') W += k;
            else B += k;
            v.pb({k, c});
        }
        if (W == 0) cout << B << nl;
        else if (B == 0) cout << W << nl;
        else {
            int ans = 0;
            ll w = 0, b = 0;
            ll w1 = 0, b1 = 0;
            F0R(i, n) {
                w1 = w; b1 = b;
                if (v[i].s == 'W') w += v[i].f;
                else b += v[i].f;
                // want to check if we can cut off a block
                // dbg(w, b, w1, b1);
                if (v[i].s == 'W') {
                    if (w*B >= W*b && w1*B < W*b1 && (W*b)%B == 0) {
                        ans++;
                        w -= (W*b)/B;
                        b = 0;
                    }
                } else {
                    if (W*b >= w*B && W*b1 < w1*B && (w*B)%W == 0) {
                        ans++;
                        b -= (w*B)/W;
                        w = 0;
                    }
                }
            }
            cout << ans << nl;
        }
        
    }
    return 0;
}
