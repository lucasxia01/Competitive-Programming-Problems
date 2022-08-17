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
    // sprague grundy
    int dp[200] = {};
    FOR(i, 1, 199) {
        set<int> s;
        F0R(j, i-1) s.insert(dp[j]^dp[i-2-j]);
        trav(ss, s) if (ss != dp[i]) break; else dp[i]++;
        // cout << dp[i] << ' ';
    } 
    // cout << nl;
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;
        int R = 0, B = 0;
        F0R(i, n) if (s[i] == 'R') R++; else B++;
        if (R > B) cout << "Alice" << nl;
        else if (B > R) cout << "Bob" << nl;
        else {

            // now split it up into RBRBRBR sequences
            string t = "";
            vi v;
            F0R(i, n) {
                if (i == 0 || s[i] == s[i-1]) {
                    v.pb(sz(t));
                    t = s[i];
                } else t += s[i];
            }
            v.pb(sz(t));
            int nim = 0;
            trav(u, v) {
                // cerr << u << " "; 
                if (u > 199) u = (u%34) + 34*3;
                nim ^= dp[u];
            }
            cout << (nim==0?"Bob":"Alice") << nl;
        }
    }
    return 0;
}
