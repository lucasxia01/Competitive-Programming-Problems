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

const int MX = 3e7;

int st[MX];
int N;

int query(int l, int r) {
    int ret = 0;
    for (l+=N, r+=N; l < r; l>>=1, r>>=1) {
        if (l&1) ckmax(ret, st[l++]);
        if (r&1) ckmax(ret, st[--r]);
    }
    return ret;
}

void upd(int i, int x) {
    for (st[i+=N]+= x; i > 1; i>>=1) st[i>>1] = max(st[i], st[i^1]);
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, q; cin >> n >> q;
        int a[n]; F0R(i, n) cin >> a[i];
        // first precompute the answer for each divisor and residue
        vi divs;
        FOR(i, 1, n-1) {
            if (n%i == 0) divs.pb(i);
        }
        // for each div, 
        vi v;
        N = 0;
        trav(d, divs) {
            int sum[d]; F0R(i, d) sum[i] = 0;
            F0R(i, n) sum[i%d] += a[i];
            F0R(i, d) {
                v.pb(sum[i]*d);
            }
            N += d;
        }
        assert(2*N < MX);
        F0R(i, N) st[i+N] = v[i];
        F0Rd(i, N) st[i] = max(st[i<<1], st[i<<1|1]);
        cout << query(0, N) << nl;
        int p, x;
        while (q--) {
            cin >> p >> x; p--;
            int cnt = 0;
            trav(d, divs) {
                int idx = cnt+(p%d);
                upd(idx, d*(x-a[p]));
                cnt+=d;
            }
            a[p] = x;
            cout << query(0, N) << nl;
        }

    }
    return 0;
}
