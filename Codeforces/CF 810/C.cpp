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
    string s; cin >> s;
    int n = sz(s);
    int dp[n+1][8][8];
    F0R(k, n+1) F0R(i, 8) F0R(j, 8) dp[k][i][j] = 0;
    dp[0][7][0] = 1;
    int m[8] = {0, 1, 2, 4, 4, 2, 1, 0};
    F0R(i, n) {
        F0R(j, 8) {
            F0R(k, 8) {
                if (dp[i][j][k] == 0) continue;
                F0R(nxt, 8) {
                    int nj = j;
                    bool ok = 1;
                    F0R(l, 3) {
                        if (j&(1<<l)) {
                            int tmp = ((s[i]-'0')<<l);
                            if ((nxt&(1<<l)) > tmp) ok = 0;
                            else if ((nxt&(1<<l)) < tmp) nj ^= (1<<l);
                        }
                    }
                    if (!ok) continue;
                    int nk = (m[nxt]|k);
                    // dbg(i, j, k, nj, nk, nxt);
                    dp[i+1][nj][nk] = (dp[i+1][nj][nk]+dp[i][j][k])%MOD;
                }
            }
        }
    }
    int ans = 0;
    F0R(i, 8) ans = (ans+dp[n][i][7])%MOD;
    cout << ans << nl;
    return 0;
}
