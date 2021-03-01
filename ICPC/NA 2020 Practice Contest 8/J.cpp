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
    int k; cin >> k;
    pair<ll, pl > a[k];
    F0R(i, k) cin >> a[i].f >> a[i].s.f >> a[i].s.s;
    ll m = 0, total = 0;
    sort(a, a+k);
    F0R(i, k) { 
        m += a[i].s.f; a[i].s.s-=a[i].s.f;
        total += a[i].s.f*a[i].f;
    }
    int r; cin >> r;
    while (r--) {
        ll x, y; cin >> x >> y;
        ll cur = y-m;
        if (cur < 0) {
            cout << "no" << nl;
            continue;
        }
        ll m1 = total, m2 = total;
        F0R(i, k) {
            if (cur >= a[i].s.s) {
                cur -= a[i].s.s;
                m1 += a[i].s.s*a[i].f;
            } else {
                m1 += cur*a[i].f;
                cur = 0;
                break;
            }
        }
        cur = y-m;
        F0Rd(i, k) {
            if (cur >= a[i].s.s) {
                cur -= a[i].s.s;
                m2 += a[i].s.s*a[i].f;
            } else {
                m2 += cur*a[i].f;
                cur = 0;
                break;
            }
        }
        if (cur > 0) {
            cout << "no" << nl;
            continue;
        }
        x *= y;
        dbg(m1, x, m2);
        cout << (m1 <= x && x <= m2 ? "yes" : "no") << nl;
    }
    return 0;
}