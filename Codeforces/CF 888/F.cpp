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
        int n, k; cin >> n >> k;
        vector<vpi> a; 
        vpi tmp(n); 
        F0R(i, n) {
            cin >> tmp[i].f;
            tmp[i].s = i;
        }
        a.pb(tmp);
        F0Rd(j, k) {
            bool eq = 0;
            vector<vpi> b;
            trav(v, a) {
                // split into buckets
                vpi x, y;
                trav(u, v) {
                    if (u.f&(1<<j)) x.pb(u);
                    else y.pb(u);
                }
                if (sz(x) >= 2) b.pb(x);
                if (sz(y) >= 2) b.pb(y);
            }
            if (sz(b)) {
                a = b;
            }
            // trav(v, a) {
            //     trav(u, v) cout << u.f << " ";
            //     cout << nl;
            // } cout << nl;
        }
        assert(sz(a) >= 1);
        int x = 0;
        pi p = a[0][0], q = a[0][1];
        F0R(i, k) {
            bool t = (p.f&(1<<i));
            bool r = (q.f&(1<<i));
            if (!t && !r) x += (1<<i);
        }
        dbg("hi", p.f, q.f);
        cout << p.s+1 << " " << q.s+1 << " " << x << nl;
    }
    return 0;
}
