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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int a[n]; F0R(i, n) cin >> a[i];
        // biggest magnitude dude and 
        int lo = 0, hi = 0;
        int loi = -1, hii = -1;
        F0R(i, n) {
            if (ckmax(hi, a[i])) hii = i;
            if (ckmin(lo, a[i])) loi = i;
        }
        int negcnt = 0, poscnt = 0;
        F0R(i, n) {
            if (a[i] < 0) negcnt++;
            if (a[i] > 0) poscnt++;
        }
        vpi ans;
        if (hi >= -lo && negcnt < 13) {
            F0R(i, n) {
                if (a[i] < 0) {
                    a[i] += hi;
                    ans.pb({i, hii});
                }
            }
            // add to 0
            FOR(i, 1, n-1) {
                ans.pb({i, i-1});
            }
        } else if (-lo >= hi && poscnt < 13) {
            F0R(i, n) {
                if (a[i] > 0) {
                    a[i] += lo;
                    ans.pb({i, loi});
                }
            }
            F0Rd(i, n-1) {
                ans.pb({i, i+1});
            }
        } else if (hi >= -lo && negcnt >= 13) {
            F0R(i, 5) ans.pb({loi, loi});
            F0R(i, n) {
                if (a[i] > 0){
                    ans.pb({i, loi});
                }
            }
            F0Rd(i, n-1) {
                ans.pb({i, i+1});
            }
        } else if (-lo >= hi && poscnt >= 13) {
            F0R(i, 5) ans.pb({hii, hii});
            F0R(i, n) {
                if (a[i] < 0){
                    ans.pb({i, hii});
                }
            }
            FOR(i, 1, n-1) {
                ans.pb({i, i-1});
            }
        }
        cout << sz(ans) <<nl;
        trav(aa, ans) cout << aa.f+1 << ' ' << aa.s+1 << nl;
    }
    return 0;
}
