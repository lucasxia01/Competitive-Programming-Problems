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
const ll MOD = 3; // 998244353
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

const int MX = 4e5+5;

template<int sz> struct Combo {
    pi fac[sz+1];
    Combo() {
        fac[0] = {1, 0};
        for (int i = 1; i <= sz; i++) {
            int j = i;
            int cnt = 0;
            while (j%3 == 0) {
                cnt++;
                j/=3;
            }
            fac[i] = {(fac[i - 1].f*j)%3, fac[i-1].s+cnt};
        }
    }

    ll comb(ll n, ll r) {
        if (n < r || n < 0 || r < 0) return 0LL;
        dbg("hi", n, r);
        dbg(fac[n].f, fac[n].s);
        dbg(fac[r].f, fac[r].s);
        dbg(fac[n-r].f, fac[n-r].s);
        if (fac[n].s > fac[r].s + fac[n-r].s) return 0LL;
        ll res = (fac[n].f * fac[r].f * fac[n - r].f) % 3;
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Combo<MX> cm;
    int n; cin >> n;
    string s; cin >> s;
    // turn it all white
    int sum = 0;
    int a[n];
    F0R(i, n) {
        if (s[i] == 'W') a[i] = 0;
        else if (s[i] == 'B') a[i] = 1;
        else a[i] = 2;
        if (n%2 == 0) a[i] = (3-a[i])%3;
        dbg(cm.comb(n-1, i), a[i]);
        sum += (cm.comb(n-1, i)*a[i])%MOD;
        sum %= MOD;
    }
    if (sum == 0) cout << 'W';
    else if (sum == 1) cout << 'B';
    else cout << 'R';
    cout << nl;
    return 0;
}
