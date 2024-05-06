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

vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string s; cin >> s;
    vi pi = prefix_function(s);
    // precalc dp
    int n = sz(s);
    int dp[n+20][26];
    F0R(j, 26) dp[0][j] = 0;
    FOR(i, 0, n-1) {
        // dbg(i, pi[i]);
        int c = s[pi[i]]-'a';
        dp[i+1][c] = pi[i]+1;
        F0R(j, 26) {
            if (j != c) dp[i+1][j] = dp[pi[i]][j];
        }
        // F0R(j, 26) cout << dp[i+1][j] << " "; cout << nl;
    }
    int q; cin >> q;
    while (q--) {
        string t; cin >> t;
        int m = sz(t);
        s += t;
        // dbg(s, n, n+m-1, s[n]);
        FOR(i, n, n+m-1) {
            // dbg("wtf", dp[i][s[i]-'a'], pi[i]);
            cout << dp[i][s[i]-'a'] << " ";
            pi.pb(dp[i][s[i]-'a']);
            int c = s[pi[i]]-'a';
            dp[i+1][c] = pi[i]+1;
            F0R(j, 26) {
                if (j != c) dp[i+1][j] = dp[pi[i]][j];
            }
        } cout << nl;

        F0R(i, m) {
            s.pop_back();
            pi.pop_back();
        }
    }
    return 0;
}
