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
const ll INF = 1e9+5;
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


struct BIT {
    int n;
    vi f;
    BIT(int n) : n(n) {
        f.resize(n+1, 0);
    }

    int query(int x) {
        int ret = 0;
        while (x) {
            // dbg("query", x);
            ret += f[x];
            x -= (x&-x);
        }
        return ret;
    }

    int search(int v) {
        int sum = 0;
        int idx = 0;
        if (v == 0) return 0;
        F0Rd(i, 20) {
            // dbg("search", idx, idx+(1<<i));
            if (idx+(1<<i) < n+1 && f[idx+(1<<i)]+sum < v) {
                idx += (1<<i);
                sum += f[idx];
            }
        }
        return idx+1;
    }

    void mod(int x, int v) {
        while (x < n+1) {
            // dbg("mod", x);
            f[x] += v;
            x += (x&-x);
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vpi a(n); F0R(i, n) {
            cin >> a[i].f;
            a[i].s = i+1;
        }
        sort(all(a));
        reverse(all(a));
        // for each element in descending order, look for how far left the next bigger is
        // look for how far right the next bigger is, and binary search for right end of 1s
        // use fenwick tree or smth
        BIT ft(n), ft2(n);
        FOR(i, 1, n) ft2.mod(i, 1);
        ll ans = 0;
        F0R(i, n-1) ans += (i+1)*(n-i-1);
        trav(p, a) {
            int sum = ft.query(p.s); // sum from 1 to p.s
            // look for first occurence of sum
            int l = ft.search(sum);
            int r = ft.search(sum+1);
            if (r < n+1) {
                int sum_r = ft2.query(r);
                int r2 = ft2.search(sum_r+1);
                dbg(p.f, p.s, sum, l, r, sum_r, r2);
                ans -= (p.s-l)*(r2-r);
            }
            ft.mod(p.s, 1);
            ft2.mod(p.s, -1);
        }
        cout << ans << nl;
    }
    return 0;
}
