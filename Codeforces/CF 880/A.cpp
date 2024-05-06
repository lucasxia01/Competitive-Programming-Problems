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
    int pows[7] = {1, 10, 100, 1000, 10000, 100000, 1000000};
    while (t--) {
        int A, B, C; ll k; cin >> A >> B >> C >> k;
        // if (max(A, B) != C && max(A, B) +1 != C) {
        //     cout << -1 << nl;
        //     continue;
        // }
        // try out all A
        ll cnt = 0;
        ll a = -1, b, c;
        rep(aa, pows[A-1], pows[A]) {
            // pows[B] > b >= pows[B-1]
            // a+b = c
            // min(pows[C], a + pows[B]) > c >= max(pows[C-1], a + pows[B-1])
            ll lo = max(pows[C-1], aa + pows[B-1]);
            ll hi = min(pows[C], aa + pows[B]);
            ll cur = max(hi - lo, 0LL);
            // dbg(aa, lo, hi, cur);
            if (cnt+cur >= k) {
                a = aa;
                c = lo + k-cnt-1;
                b = c - a;
                cnt += cur;
                break;
            }
            cnt += cur;
        }

        if (cnt < k) {
            cout << -1 << endl;
        } else {
            cout << a << " + " << b << " = " << c << nl;
        }
    }
    return 0;
}
