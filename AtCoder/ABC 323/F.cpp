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

ll dist (pi a, pi b) {
    return abs(a.f-b.f) + abs(a.s-b.s);
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    vpl v(3);
    F0R(i, 3) {
        int a, b; cin >> a >> b;
        v[i] = {a, b};
    }
    // now check if b is aligned with c
    vpi pos;
    if (v[1].f!=v[2].f) {
        if (v[1].f < v[2].f) {
            pos.pb({v[1].f-1, v[1].s});
        } else {
            pos.pb({v[1].f+1, v[1].s});
        }
    }
    if (v[1].s!=v[2].s) {
        if (v[1].s < v[2].s) {
            pos.pb({v[1].f, v[1].s-1});
        } else {
            pos.pb({v[1].f, v[1].s+1});
        }
    }
    int ans = 0;
    int lo = 1e18;
    trav(p, pos) {
        // if you have to go through the cargo, +2
        int tmp = 0;
        if (v[0].f==v[1].f && v[1].f==p.f) {
            if (v[0].s < v[1].s && v[1].s < p.s) tmp += 2;
            if (v[0].s > v[1].s && v[1].s > p.s) tmp += 2;
        }
        if (v[0].s==v[1].s && v[1].s==p.s) {
            if (v[0].f < v[1].f && v[1].f < p.f) tmp += 2;
            if (v[0].f > v[1].f && v[1].f > p.f) tmp += 2;
        }
        ckmin(lo, dist(v[0], p)+tmp);
    }
    ans += lo;
    ans += dist(v[1], v[2]);
    if (sz(pos) == 2) ans += 2;
    cout << ans << nl;
    return 0;
}
