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

vector<pair<pl, char> > ops;

ll gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

void twice(ll x) {
    ops.pb({{x, x}, '+'});
}
void mult(ll x, ll a) {
    if (a == 2) {
        twice(x);
        return;
    }
    ll cur = x;
    ll sum = 0;
    ll pow = 1, exp = 1;
    while (pow < a) {
        pow*=2;
        exp++;
    }
    F0R(i, exp) {
        ops.pb({{cur, cur}, '+'});
        if (a&(1LL<<i)) {
            ops.pb({{sum, cur}, '+'});
            sum += cur;
        }
        cur *= 2;
    }
}

void x_or(ll a, ll b) {
    ops.pb({{a, b}, '^'});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll x; cin >> x;
    x_or(x, x); // for 0
    int exp = 0;
    ll pow = 1;
    while (2*pow <= x) {
        pow *= 2;
        exp++;
    }
    ll cur = x;
    F0R(i, exp) {
        twice(cur);
        cur *= 2;
    }
    x_or(cur, x);
    // we have a number that has gcd 1 with x
    ll y = cur^x;
    ll a, b;
    gcd(y, x, a, b);
    a = abs(a); b = abs(b);
//    cout << y << " " << x << " " << a << " " << b << nl;
    mult(y, a);
    mult(x, b);
    y *= a;
    x *= b;
    assert(abs(x-y)==1);
    if ((x^y)!=1) {
        twice(min(x,y));
        ops.pb({{x, y}, '+'});
        ll temp = x+y;
        x = 2*min(x,y);
        y = temp;
    }
    x_or(y, x);
    cout << sz(ops) << nl;
    trav(op, ops) {
        cout << op.f.f << " " << op.s << " " << op.f.s << nl;
    }
    return 0;
}
