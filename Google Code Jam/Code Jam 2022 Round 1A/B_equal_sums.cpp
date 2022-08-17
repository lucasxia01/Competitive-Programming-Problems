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
    F0R(tt, t) {
        int n; cin >> n;
        dbg(n);
        if (n == -1) return 0;
        // we want to use 32 numbers for 2^0, .. 2^30
        vl v;
        F0R(i, 30) v.pb(1<<i);
        v.pb((1<<29) + 1);
        v.pb((1<<29) - 1);
        // for remaining 68, pick whatever
        vl w;
        F0R(i, 68) {
            v.pb(1e9-i);
            w.pb(1e9-i);
        }
        ll total = 0;
        trav(u, v) total += u;
        assert(sz(v) == 100);
        trav(u, v) cout << u << " "; cout << endl;
        cout.flush();

        vi ans1, ans2, ans;
        ll sum1 = 0, sum2 = 0;
        F0R(i, n) {
            int x; cin >> x;
            if (x == -1) return 0;
            total += x;
            w.pb(x);
        }
        trav(u, w) {
            if (sum1 < sum2) {
                sum1 += u;
                ans1.pb(u);
            } else {
                sum2 += u;
                ans2.pb(u);
            }
        }
        assert(abs(sum1-sum2) <= 1e9);
        ll diff = abs(sum1 - sum2);
        if (sum1 > sum2) ans = ans1;
        else ans = ans2;
        assert(diff%2 == 1);
        diff = diff/2;
        dbg(diff, sum1, sum2);
        // now with remaining things, we win
        F0R(i, 30) {
            if (!(diff&(1<<i))) {
                ans.pb(1<<i);
            }
        }
        
        ll half = 0;
        trav(aa, ans) half += aa;
        dbg(total, half);
        trav(aa, ans) cout << aa << " "; cout << endl;
        cout.flush();
    }
    return 0;
}
