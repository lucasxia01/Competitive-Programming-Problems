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
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

int calcdiff(int x, int b) {
    return max(x-b, 0)-(x+1)/2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, b, k1, k2; cin >> n >> b >> k1 >> k2;
        int a[n]; F0R(i, n) cin >> a[i];
        sort(a, a+n);
        // try 0 through min(k1, k2)
        ll ans = 0;
        F0R(i, n) ans += a[i];
        F0R(k, min(k1, k2)+1) {
            int x = k1-k, y = k2-k;
            int m = n-k;
            ll tmp = 0;
            FOR(j, m, n-1) tmp += max(0, (a[j]+1)/2 - b);
            vi v;
            // get the x+y biggest dudes
            FORd(j, max(0, m-x-y), m-1) v.pb(a[j]); // biggest to smallest
            vi better1, better2, same;
            trav(u, v) {
                int v1 = (u+1)/2;
                int v2 = max(u-b, 0);
                if (v1 < v2) better1.pb(u);
                else if (v2 < v1) better2.pb(u);
                else same.pb(u);
            }
            int l = 0, r = sz(better2);
            if (sz(better1) > x) {
                // too many halfs
                while (sz(better1) > x) {
                    better2.pb(better1.back());
                    better1.pop_back();
                }
                r = sz(better2);
            } else if (sz(better2) > y) {
                // too many -bs
                while (r-l > y) {
                    int tmp1 = calcdiff(better2[l],b);
                    int tmp2 = calcdiff(better2[r-1],b);
                    if (tmp1 > tmp2) better1.pb(better2[l++]);
                    else better1.pb(better2[--r]);
                }
            }
            trav(u, better1) tmp += (u+1)/2;
            trav(u, same) tmp += (u+1)/2;
            FOR(j, l, r-1) tmp += max(better2[j]-b, 0);
            F0R(j, max(0, m-x-y)) tmp += a[j];
            ckmin(ans, tmp);

        }
        cout << ans << nl;
    }
    return 0;
}
