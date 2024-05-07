#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
#define int ll

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
#define rep(i, a, b) for(int i = a; i < (b); ++i)

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
const ll MOD = 1000000007LL; // 998244353
const ll MOD2 = 1000000009LL;
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(...) dbg_out(__VA_ARGS__);
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){
	c << "(" << v.fi << "," <<v.se <<")"; return c;
}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){
	out << "{ ";
	trav(x,c) out<<x<<" ";
	out<<"}"; return out;
}
#else
#define dbg(...)
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e6+5;

int n, m;

struct ST {
    int t[2 * MX];
    ST(vi v) {
        F0R(i, n) t[i+n] = v[i];
        build();
    }
    void build() {  // build the tree
    for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
    }

    void modify(int p, int value) {  // set value at position p
    for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
    }

    int query(int l, int r) {  // sum on interval [l, r)
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) res += t[l++];
        if (r&1) res += t[--r];
    }
    return res;
    }
};

void solve() {
    cin >> n >> m;
    vi b(n, 0), c(n, 0), d(n, 0);
    vi a(n); 
    int sum = 0;
    F0R(i, n) {
        cin >> a[i];
        sum += a[i];
        b[i] = (a[i]==1);
        if (a[i]==1) c[i] = i;
        else d[i] = i;
    }
    ll ans = 0;
    ST cnt(b);
    ST sum1(c), sum2(d);
    while (m--) {
        int x, y, z; cin >> x >> y >> z;
        x--; z--;
        // update x to y
        if (a[x] == 1) {
            cnt.modify(x, 0);
            sum1.modify(x, 0);
        } else {
            sum2.modify(x, 0);
        }
        sum -= a[x];
        a[x] = y;
        sum += y;
        if (a[x] == 1) {
            cnt.modify(x, 1);
            sum1.modify(x, x);
        } else {
            sum2.modify(x, x);
        }

        if (sum%2) {
            ans += -1;
            continue;
        }

        int num2 = sum/2-z-1;
        int num1 = z+1 - num2;
        // dbg(num1, num2);
        int total1 = cnt.query(0, n), total2 = n-total1;
        if (num1 < 0 || num2 < 0 || total1 < num1 || total2 < num2) {
            ans += -1;
            continue;
        }
        // now binary search for the position
        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = (lo+hi)/2;
            if (cnt.query(0, mid) < num1) lo = mid+1;
            else hi = mid;
        }
        int val1 = sum1.query(0, lo) - sum1.query(0, z+1);
        int lo1 = lo;
        lo = 0; hi = n;
        while (lo < hi) {
            int mid = (lo+hi)/2;
            if (mid-cnt.query(0, mid) < num2) lo = mid+1;
            else hi = mid;
        }
        int val2 = sum2.query(0, lo) - sum2.query(0, z+1);
        // dbg(lo1, val1, lo, val2);
        if (val1 > 0) ans += val1+val2;
        else ans += val2+val1;
    }
    cout << ans << nl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    FOR(i, 1, t) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
