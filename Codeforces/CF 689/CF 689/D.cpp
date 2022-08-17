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

const int MX = 1e5+5;

int n;
vpi ranges;
vl a(MX);
void solve(int l, int r) { // [l, r] of a
    if (r < l) return;
    ranges.pb({l, r});
    if (r == l) return;
    ll mid = (a[l]+a[r])/2;
//    cout << l << " " << r << " " << mid << nl;
    int idx = upper_bound(a.begin(), a.begin()+n, mid)-a.begin();
    if (idx > r) {
        F0R(i, n) cout << a[i] << " "; cout << nl;
        dbg_out(mid, idx, r);
        return;
    }
    solve(l, idx-1);
    solve(idx, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int q; cin >> n >> q;
        F0R(i, n) cin >> a[i];
        sort(a.begin(), a.begin()+n);
        ll pre[n+1]; pre[0] = 0LL; F0R(i, n) pre[i+1] = pre[i]+a[i];
        set<ll> sums;
        ranges.clear();
        solve(0, n-1);
        trav(p, ranges) {
            sums.insert(pre[p.s+1]-pre[p.f]);
        }
        ll s;
        F0R(i, q) {
            cin >> s;
            if (sums.find(s) != sums.end()) cout << "Yes" << nl;
            else cout << "No" << nl;
        }
    }
    return 0;
}
