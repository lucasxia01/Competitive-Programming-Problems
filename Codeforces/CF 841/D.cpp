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
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        int a[n][m]; F0R(i, n) F0R(j, m) cin >> a[i][j];
        // first sparse table
        int t[20][n][m];
        F0R(i, n) F0R(j, m) t[0][i][j] = a[i][j];

        F0R(k, 19) {
            F0R(i, n) F0R(j, m) {
                t[k+1][i][j] = 0;
                if (i >= (1<<k) && j >= (1<<k)) {
                    t[k+1][i][j] = min(min(t[k][i][j], t[k][i-(1<<k)][j]), min(t[k][i][j-(1<<k)], t[k][i-(1<<k)][j-(1<<k)]));
                }
                // if (k == 1) {
                //     dbg(i, j, t[k][i][j]);
                // }
            }
        }

        // bin search
        int lo = 1, hi = 1e6;
        while (lo < hi) {
            int mid = (lo+hi)/2;
            // power of 2 just smaller
            int pow = 31 - __builtin_clz(mid);
            // dbg(pow);
            bool ok = 0;
            int diff = mid - (1<<pow);
            F0R(i, n) F0R(j, m) {
                if (i >= diff && j >= diff) {
                    int c = min(min(t[pow][i][j], t[pow][i-diff][j]), min(t[pow][i][j-diff], t[pow][i-diff][j-diff]));
                    if (c >= mid) {
                        ok = 1;
                        break;
                    }
                }
            }
            if (ok) lo = mid+1;
            else hi = mid;
        }
        cout << lo-1 << nl;
    }
    return 0;
}
