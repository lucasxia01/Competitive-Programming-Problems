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
    while (t--) {
        int n, m; cin >> n >> m;
        string s, t; cin >> s >> t;
        int dp[n+1][m+1]; F0R(i, n+1) F0R(j, m+1) dp[i][j] = INF;
        dp[0][0] = 0;
        F0R(i, n) {
            F0R(j, m+1) {
                if (dp[i][j] == INF) continue;
                ckmin(dp[i+1][j], i+1);
                if (j < m && s[i] == t[j]) ckmin(dp[i+1][j+1], dp[i][j]);
            }
        }
        if (dp[n][m] == INF) {
            cout << -1 << nl;
            continue;
        }
        reverse(all(s)); reverse(all(t));
        int dp2[n+1][m+1]; F0R(i, n+1) F0R(j, m+1) dp2[i][j] = 0;
        dp2[0][0] = 1;
        F0R(i, n) {
            F0R(j, m+1) {
                if (!dp2[i][j]) continue;
                dp2[i+1][j] = 1;
                if (j < m && s[i] == t[j]) dp2[i+1][j+1] = 1;
            }
        }
        int ans = INF;
        F0R(i, n+1) {
            // now for all possible suffixes
            F0R(j, m+1) {
                int tmp = n-i;
                if (dp2[n-i][m-j]) {
                    if (dp[i][j] != INF) {
                        if (i-j) tmp++;
                        tmp += i-j;
                        tmp += dp[i][j];
                        // dbg(i, j, tmp, dp[i][j]);
                        ckmin(ans, tmp);
                    }
                }
            }
        }
        cout << ans << nl;
    }
    return 0;
}
