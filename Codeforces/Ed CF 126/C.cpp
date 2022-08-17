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

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        ll a[n]; F0R(i, n) cin >> a[i];
        pl b = {0, 0}, c = {0, 0};
        ll hi = *max_element(a, a+n);
        F0R(i, n) {
            ll x = hi-a[i];
            b.f+=x;
            c.f += (x%2);
            c.s += x/2;
        }
        dbg(b.f, b.s, c.f, c.s);
        // somewhere in between where f + 2s = b.f and min(2f-1, 2s) is minimized
        pl guess = {b.f - 2*((b.f - b.f/3)/2), (b.f - b.f/3)/2};
        assert(guess.f + 2*guess.s == b.f);
        dbg(guess.f, guess.s);
        ll ans = max(2*c.f-1, 2*c.s);
        FOR(i, -10, 10) {
            pl t = {guess.f - 2*i, guess.s + i};
            if (t.s >= 0 && t.s <= c.s) {
                ckmin(ans, max(2*t.f-1, 2*t.s));
            }
        }

        b = {0, 0}, c = {0, 0};
        hi = *max_element(a, a+n) + 1;
        F0R(i, n) {
            ll x = hi-a[i];
            b.f+=x;
            c.f += (x%2);
            c.s += x/2;
        }
        b.f--; c.f--;
        dbg(b.f, b.s, c.f, c.s);
        // somewhere in between where f + 2s = b.f and min(2f-1, 2s) is minimized
        guess = {b.f - 2*((b.f - b.f/3)/2), (b.f - b.f/3)/2};
        assert(guess.f + 2*guess.s == b.f);
        dbg(guess.f, guess.s);
        ckmin(ans, max(2*c.f+1, 2*c.s));
        FOR(i, -10, 10) {
            pl t = {guess.f - 2*i, guess.s + i};
            if (t.s >= 0 && t.s <= c.s) {
                ckmin(ans, max(2*t.f+1, 2*t.s));
            }
        }
        cout << ans << nl;
    }
    return 0;
}
