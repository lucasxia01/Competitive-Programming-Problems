#include <bits/stdc++.h>

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
#define rep(i, a, b) for(int i = a; i < (b); ++i)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define ins insert
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
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll n, m, k; cin >> n >> m >> k;
    ll a[n]; F0R(i, n) cin >> a[i];
    sort(a, a+n);
    auto calc = [&] (ll cur) -> ll {
        ll total = 0;
        if (cur < 0 || cur > m) return 0;
        int ub = (upper_bound(a, a+n, cur)-a);
        int lb = (lower_bound(a, a+n, cur)-a);
        int idxl = ub - k;
        if (idxl < 0) {
            total += cur;
        } else {
            total += (cur-a[idxl]-1)/2;
        }
        int idxr = lb + (k-1);
        // dbg(cur, idxl, idxr);
        if (idxr >= n) total += m-cur;
        else total += (a[idxr]-cur-1)/2;
        // check if there are more than k at current spot
        if (ub - lb < k) total++;
        return total;
    };

    // try all a[i] and in between try 2 or 3
    ll hi = -1, ans = -1;
    // try 0 and 1 first
    if (ckmax(hi, calc(0))) ans = 0;
    if (ckmax(hi, calc(1))) ans = 1;
    F0R(i, n) {
        // try placing at all a[i] +/- 2
        rep(j, -2, 3) {
            ll cur = a[i]+j;
            ll total = calc(cur);
            if (ckmax(hi, total)) ans = cur;
        }
    }
    
    cout << hi << " " << ans << nl;
    return 0;
}
