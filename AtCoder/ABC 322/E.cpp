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
const ll INF = 1e15 + 123;
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
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 6*6*6*6*6;

int n, k, p;
int conv(vi v) {
    int ret = 0;
    int pow = 1;
    F0R(i, k) {
        if (v[i] > p) v[i] = p;
        ret += pow*v[i];
        pow *= (p+1);
    }
    return ret;
}
vi rconv(int x) {
    vi ret;
    F0R(i, k) {
        ret.pb(x%(p+1));
        x /= (p+1);
    }
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> k >> p;
    vector<pair<int, vi > > v(n);
    F0R(i, n) {
        v[i].s.resize(k);
        cin >> v[i].f;
        F0R(j, k) cin >> v[i].s[j];
    }
    int test = 73;
    dbg(conv(rconv(test)));
    int M = 1;
    F0R(i, k) M *= (p+1);
    ll dp[n+1][M];
    F0R(j, n+1) F0R(i, M) dp[j][i] = INF;
    dp[0][0] = 0;
    F0R(i, n) {
        F0R(j, M) {
            if (dp[i][j] == INF) continue;
            ckmin(dp[i+1][j], dp[i][j]);
            vi cur = rconv(j);
            F0R(l, k) cur[l] += v[i].s[l];
            int nxt = conv(cur);
            ckmin(dp[i+1][nxt], dp[i][j]+v[i].f);
        }
    }
    
    if (dp[n][M-1] == INF) cout << -1 << nl;
    else cout << dp[n][M-1] << nl;
    return 0;
}
