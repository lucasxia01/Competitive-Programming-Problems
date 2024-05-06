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
const ll INF = (1LL<<29) + 123;
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    ll a[n]; F0R(i, n) cin >> a[i];
    ll A[n]; F0R(i, n) A[i] = a[i];
    // and also with everything with bit i not set, being 0 or initial value
    // decompose a into bits first
    // vector<bool> b[n];
    // F0R(i, n) {
    //     F0R(j, 60) {
    //         b[i].pb(A[i]%2);
    //         A[i]/=2;
    //     }
    // }
    // ll val[60][2]; F0R(i, 60) val[i][0] = val[i][1] = 0;
    // F0R(i, 60) {
    //     // getting to bit i being set
    //     F0R(j, n) {
    //         if (!b[j][i]) {
    //             val[i][0] += (1LL<<i) - (a[j]&((1LL<<i)-1));
    //             if (i == 1) {
    //                 dbg(i, j, a[j], val[i][0], (1LL<<i) - (a[j]&((1LL<<i)-1)));
    //             }
    //             if (val[i][0] > 1e18) val[i][0] = -1;
    //         }
    //         val[i][1] += (1LL<<i);
    //         if (val[i][1] > 1e18) val[i][1] = -1;
    //     }
    //     dbg(i, val[i][0], val[i][1]);
    // }

    while (q--) {
        ll k; cin >> k;
        // find highest bit we can do
        ll ans = 0;
        int i = 59;
        F0R(j, n) a[j] = A[j];
        while (i >= 0) {
            // calculate it for a
            bool ok = 1;
            ll cnt = 0;
            F0R(j, n) {
                if (!(a[j]&(1LL<<i))) {
                    cnt += (1LL<<i) - (a[j]&((1LL<<i)-1));
                    if (cnt > k) {
                        ok = 0;
                        break;
                    }
                }
            }
            // dbg(i, ok, cnt);
            if (ok) {
                ans |= (1LL<<i);
                k -= cnt;
                // update the ans
                F0R(j, n) {
                    if (!(a[j]&(1LL<<i))) a[j] = 0;
                }
            }
            i--;
        }
        cout << ans << nl;
    }
    return 0;
}
