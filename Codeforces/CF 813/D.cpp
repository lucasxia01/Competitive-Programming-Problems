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
const ll INF = 1e9;
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
        int n, k; cin >> n >> k;
        int a[n]; F0R(i, n) cin >> a[i];
        if (n == 2) {
            if (k == 1) cout << max(a[0], a[1]) << nl;
            else cout << INF << nl;
            continue;
        }
        map<int, vi> s; 
        F0R(i, n) {
            if (s.find(a[i]) == s.end()) {
                vi tmp; tmp.pb(i);
                s[a[i]] = tmp;
            } else s[a[i]].pb(i);
        }
        
        int cur = 0;
        F0R(i, n-1) ckmax(cur, min(a[i], a[i+1]));
        int HI = 0;
        F0R(i, n) ckmax(HI, a[i]);
        int cnt = 0;
        int ans = 0;

        trav(p, s) {
            if (cnt > k) break;
            // dbg(cnt, 2*p.f, k+p.s);
            int val = cur;
            if (cnt == 0 && k == 1) val = HI;
            else if (k-cnt > 0) val = INF; 
            dbg(2*p.f, val);
            ckmax(ans, min(2*p.f, val));
            cnt += sz(p.s);
            trav(u, p.s) {
                a[u] = INF;
                if (u > 0) ckmax(cur, a[u-1]);
                if (u < n-1) ckmax(cur, a[u+1]);
            }
        }
        if (k == n) ans = INF;
        cout << ans << nl;
    }
    return 0;
}
