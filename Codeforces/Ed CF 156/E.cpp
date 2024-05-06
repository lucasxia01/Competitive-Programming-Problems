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
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    int a[n]; F0R(i, n) cin >> a[i];
    int b[m]; F0R(i, m) cin >> b[i];
    vpi v(n);
    F0R(i, n) v[i] = mp(a[i], i);
    sort(all(v)); reverse(all(v));
    // for each project, calculate the first time when we can use i people to finish it
    int minAmt[m][n]; F0R(i, m) F0R(j, n) minAmt[i][j] = INF;
    F0R(j, m) {
        F0Rd(i, n) {
            int start = i-(b[j]+v[i].f-1)/v[i].f+1;
            if (start < 0) continue;
            ckmin(minAmt[j][start], i+1);
        }
        F0Rd(i, n-1) {
            ckmin(minAmt[j][i], minAmt[j][i+1]);
        }
    }
    int dp[(1<<m)]; F0R(i, (1<<m)) dp[i] = INF;
    array<int, 4> par[(1<<m)]; 
    F0R(i, (1<<m)) {
        if (i == 0) {
            dp[i] = 0;
            par[i] = {-1, -1};
            continue;
        }
        F0R(j, m) {
            if (i&(1<<j)) {
                int ii = (i^(1<<j));
                if (dp[ii] == INF) continue;
                if (minAmt[j][dp[ii]] != INF) {
                    if (ckmin(dp[i], minAmt[j][dp[ii]])) {
                        par[i] = {ii, j, dp[ii], minAmt[j][dp[ii]]};
                    }
                }
            }
        }
    }
    if (dp[(1<<m)-1] == INF) {
        cout << "NO" << nl;
    } else {
        cout << "YES" << nl;
        int cur = (1<<m)-1;
        pi ans[m];
        while (cur > 0) {
            ans[par[cur][1]] = {par[cur][2], par[cur][3]};
            cur = par[cur][0];
        }
        F0R(i, m) {
            cout << ans[i].s-ans[i].f;
            FOR(j, ans[i].f, ans[i].s-1) cout << " " << v[j].s+1;
            cout << nl;
        }
    }
    return 0;
}
