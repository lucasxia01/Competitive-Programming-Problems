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
const ll MOD = 1000000007; // 998244353
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
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

int gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

__int128_t roundup(__int128_t a, __int128_t b) {
    if (a < 0) {
        return -((-a)/b);
    } else {
        return (a+b-1)/b;
    }
}

__int128_t rounddown(__int128_t a, __int128_t b) {
    if (a >= 0) return a/b;
    return -((-a + b-1)/b);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll n, a, b, c, x; cin >> n >> a >> b >> c >> x;
    ll ans = 0;
    FOR(i, 1, n) {
        ll y = x - a*i;
        if (y < 0) continue;
        // now extended euclidean
        ll j, k;
        ll g = gcd(b, c, j, k);
        if (y % g != 0) continue;
        y/=g;
        int bb = b/g, cc = c/g;
        __int128_t J = (__int128_t)j*y; // maybe out of bounds here
        __int128_t K = (__int128_t) k*y; // maybe out of bounds here
        // dbg(y, bb, cc, j, k);
        // j + jj*cc needs to be in range [1, n]
        // k - jj*bb needs to be in range [1, n]
        // round up (1-j / cc), round 
        // dbg(roundup(1-J, cc), roundup(k-n, bb));
        // dbg(rounddown(n-J, cc), rounddown(k-1, bb));
        __int128_t l = max(roundup(1-J, cc), roundup(K-n, bb));
        __int128_t r = min(rounddown(n-J, cc), rounddown(K-1, bb));
        ans += max(__int128_t(0), (r-l+1));
    }
    cout << ans << nl;
    return 0;
}
