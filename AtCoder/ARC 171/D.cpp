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
    int p, b, n, m; cin >> p >> b >> n >> m;
    n++;
    int l[m], r[m];
    int mat[n][n]; F0R(i, n) F0R(j, n) mat[i][j] = 0;
    F0R(i, m) {
        cin >> l[i] >> r[i];
        l[i]--;
        mat[l[i]][r[i]] = mat[r[i]][l[i]] = 1;
    }
    // see if this graph is p-colorable
    // first find all the independent sets
    bool indep[1<<n]; indep[0] = 1;
    ll MASK = (1<<n)-1;
    FOR(i, 1, MASK) {
        int submask = i - (i&-i);
        bool ok = 1;
        if (indep[submask]) {
            // check if this bit is independent from the rest
            int k = __builtin_ctz(i&-i);
            F0R(j, n) {
                if (submask&(1<<j)) {
                    if (mat[k][j]) {
                        ok = 0;
                        break;
                    }
                }
            }
        } else ok = 0;
        indep[i] = ok;
    }

    // now do the dp for k-coloring
    int dp[1<<n]; dp[0] = 0;
    FOR(i, 1, MASK) {
        // iterate over all submasks
        if (indep[i]) dp[i] = 1;
        else dp[i] = INF;
        for (int s=i-1; s>0; s=((s-1)&i)) {
            if (!indep[s]) continue;
            ckmin(dp[i], dp[i^s]+1);
        }
    }
    dbg(dp[MASK]);
    cout << (dp[MASK] <= p ? "Yes" : "No") << nl;

    return 0;
}
