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

int n;
int st[2*MX];

void mod(int i, int v) {
    for (st[i+=n] = v; i > 1; i>>=1) {
        st[i>>1] = min(st[i], st[i^1]);
    }

}

int query(int l, int r) {
    int res = INF;
    for (l += n, r += n; l < r; l>>=1, r>>=1) {
        if (l&1) res = min(res, st[l++]);
        if (r&1) res = min(res, st[--r]);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        F0R(i, 2*n) st[i] = INF;
        int a[n]; F0R(i, n) cin >> a[i];
        int b[n]; F0R(i, n) cin >> b[i];
        int rev[n];
        vi pos[n], posb[n]; 
        F0R(i, n) pos[a[i]-1].pb(i);
        F0R(i, n) posb[b[i]-1].pb(i);

        int j = 0;
        int jb = 0;
        bool ok = 1;
        F0R(i, n) {
            if (sz(pos[i]) != sz(posb[i])) ok = 0;
            trav(x, pos[i]) {
                dbg(j);
                rev[j] = x;
                a[x] = j++;
            }
            trav(x, posb[i]) b[x] = jb++;
        }
        // now go sicko mode
        F0R(i, n) mod(i, a[i]);
        F0R(i, n) {
            if (query(0, rev[b[i]]+1) != b[i]) {
                ok = 0;
                break;
            }
            mod(rev[b[i]], INF);
        }
        cout << (ok ? "YES" : "NO") << nl;

    }
    return 0;
}
