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
bool a[10] = {};

// find largest digit less than x
int smaller(int x) {
    F0Rd(i, x) {
        if (!a[i]) return i;
    }
    return -1;
}

// find smallest digit greater than x
int larger(int x) {
    FOR(i, x+1, 9) {
        if (!a[i]) return i;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll x; cin >> x;
    vl v;
    string s = to_string(x);
    int n = sz(s);
    F0R(i, n) a[s[i]-'0'] = 1;
    if (!a[0]) v.pb(0);
    // first check if digit is avail
    bool ok = 0;
    F0R(i, 10) if (!a[i]) ok = 1;
    if (!ok) {
        cout << "Impossible" << nl;
        return 0;
    }
    // can add a digit or just go down or up
    // go down
    string t = "";
    int y = smaller(s[0]-'0');
    if (y > 0) {
        t += (y+'0');
        int z = smaller(10);
        F0R(i, n-1) t += (z+'0');
        cerr << t << nl;
        v.pb(stoll(t));
    } else {
        // remove a digit
        t = "";
        y = smaller(10);
        if (n > 1 && y > 0) {
            F0R(i, n-1) t += (y+'0');
            cerr << t << nl;
            v.pb(stoll(t));
        }
    }

    t = "";
    y = larger(s[0]-'0');
    if (y > 0) {
        t += (y+'0');
        int z = larger(-1);
        F0R(i, n-1) t += (z+'0');
        cerr << t << nl;
        v.pb(stoll(t));
    } else {
        t = "";
        y = larger(0);
        if (y > 0) {
            t += (y+'0');
            y = larger(-1);
            F0R(i, n) t += (y+'0');
            cerr << t << nl;
            v.pb(stoll(t));
        }
    }

    assert(sz(v));
    vpl ans;
    trav(vv, v) {
        ans.pb({llabs(x-vv), vv});
    }
    sort(all(ans));
    trav(aa, ans) {
        if (aa.f == ans[0].f) cout << aa.s << " ";
    }
    cout << nl;
    return 0;
}
