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

const int MX = 1e6+5;

// 1, 1
// 3, 4
// 5, 7
// 7, 10
// 2, 2
// 4, 5
// 6, 8

// a, b, a-b, a-2b, b, a-3b, a-4b, b
// 1 7 6 1 5 4 1 3 2 1 1 0 1 1 0 1 1 0 1 1 
// 2 6 4 2 2 0 2 2 0 2 2 0
// 4 4 0 4 4 0 4 4 0 4 4 0
// 5 3 2 1 1 0
int cnt(int a, int b) {
    if (a < b) return (1 + cnt(b, b-a));
    if (b == 0) return 0;
    int c = a/b;
    int r = a%b;
    if (c%2 == 0) return (3*(c/2)-1 + cnt(r+b, r));
    else return (3*(c/2)+1 + cnt(b, r));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vi a(n); F0R(i, n) cin >> a[i];
        vi b(n); F0R(i, n) cin >> b[i];
        int c = -1;
        bool ok = 1;
        F0R(i, n) {
            if (a[i] == 0 && b[i] == 0) continue;
            int cur = cnt(a[i], b[i])%3;
            dbg(a[i], b[i], cur);
            if (c == -1) {
                c = cur;
            } else if (cur != c) {
                ok = 0; break;
            }
        }
        cout << (ok ? "YES" : "NO") << nl;
    }
    return 0;
}
