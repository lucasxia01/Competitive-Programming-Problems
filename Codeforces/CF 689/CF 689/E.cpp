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

ll gcd(ll a, ll b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a%b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll k, l, r, t, x, y; cin >> k >> l >> r >> t >> x >> y;
    if (x >= y) {
        if (k+y <= r) k+=y;
        k-=x;
        // after t-1 more days
        if (k < l) {
            cout << "No" << nl;
            return 0;
        }
        if (x > y) {
//            cout << (k-(l-1) +(x-y-1))/(x-y) << nl;
            cout << ((t-1 >= (k-(l-1) +(x-y-1))/(x-y))?"No":"Yes") << nl;
        } else cout << ((k < l)?"No":"Yes") << nl;
    } else { // x < y
//        if (r-y-x+1 < l) cout << "No" << nl;
        // range = [r-y-x+1, r-y]
        if (k+y <= r) k+=y; // first morning
        // first we check if we even need to do stuff
        if ((k-(l-1)+(x-1))/x > t || r-y-x+1 >= l) {
            cout << "Yes" << nl;
            return 0;
        }
        
        ll start = (k-(r-y)+(x-1))/x; // initial amount to get into the range
        vpl process;
        ll cur = k;
        cur -= ((cur-(r-y)+(x-1))/x * x);
        while (1) {
            ll amt = cur;
            cur += y;
            ll days = (cur-(r-y)+(x-1))/x;
            process.pb({amt, days});
            cur -= (days * x);
            if (cur == process[0].f) break; // must reach here since only x values
        }
        ll total = start;
        trav(a, process) {
            if (total >= t && a.f >= l) {
                cout << "Yes" << nl;
                return 0;
            }
            if (a.f < l) {
                cout << "No" << nl;
                return 0;
            }
            if (total + a.s-1 >= t) {
                cout << "Yes" << nl;
                return 0;
            }
            total += a.s;
        }
        // we can just loop infinitely with no worries
        cout << "Yes" << nl;
    }
    return 0;
}
