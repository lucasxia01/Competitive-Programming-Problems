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
const ll MOD = 998244353;
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
    int n; cin >> n;
    vi a(n); F0R(i, n) cin >> a[i];
    int dp[n]; F0R(i, n) dp[i] = 0;
    int pref[n+1]; pref[0] = 0;
    dp[0] = pref[1] = 1;
    int rep[n]; rep[0] = 0;
    int prev = 0;
    FOR(i, 1, n-1) {
        if (a[i] == a[i-1]) {
            prev = i;
            dp[i] = dp[i-1];
        } else {
            if (i-2 < prev || a[i] != a[i-2]) {
                dp[i] = (pref[i]-pref[prev]+MOD)%MOD;
            } else {
                int j = max(prev-1, max(rep[i-1], rep[i-2])-2);
                dp[i] = (((pref[j+1]-pref[prev]+MOD)%MOD) + ((dp[i-1]+dp[i-2])%MOD))%MOD;
            }
        }
        if (i-2 >= 0 && a[i] == a[i-2]) rep[i] = rep[i-2];
        else rep[i] = i;
        pref[i+1] = (pref[i] + dp[i]) % MOD;
        dbg(i, a[i], dp[i]);
    }
    cout << dp[n-1] << nl;
    return 0;
}
