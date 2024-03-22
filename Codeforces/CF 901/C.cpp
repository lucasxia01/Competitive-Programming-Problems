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

const int MX = 2e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // precompute the probabilities for the even case
    vector<ld> p[5001];
    p[2] = {0.5, 0};
    for (int k = 4; k <= 5000; k+=2) {
        p[k].pb((ld)1/k);
        // for the rest, we can apply a (i-1)/i multiplier
        FOR(j, 0, k-3) {
            ld tmp = 0;
            if (j > 0) tmp += ((ld)j/(k-1)) * (p[k-2][j-1]);
            tmp += (ld)(k-2-j)/(k-1) * p[k-2][j]; // from p[i-2][j+1]
            tmp *= (ld)(k-1)/k;
            p[k].pb(tmp);
        }
        p[k].pb(0);
    }

    int t = 1; 
    cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        vi gr[n+1];
        F0R(i, m) {
            int a, b; cin >> a >> b;
            gr[a].pb(b);
        }
        // now dp in reverse
        ld dp[n+1];
        dp[n] = 1;
        FORd(i, 1, n-1) {
            // given number of edges, compute probabilities
            int k = sz(gr[i]); // num of edges
            dbg("i with edge count", i, k);
            // probability that we fail at least i times is
            // P(i) = (k-1)/k * (k-3)/(k-2) * ... * (k+1-2*i)/(k-2*(i-1))
            // P(0) = 1
            // so the probability that we fail exactly i times is P(i) - P(i+1)

            // order the edges to choose
            vector<pair<ld, int> > es;
            trav(u, gr[i]) {
                es.pb({dp[u], u});
            }
            sort(all(es));
            reverse(all(es));
            dp[i] = 0;
            if (k%2) {
                // all are equal probability of 1/k
                F0R(j, k) {
                    dp[i] += (ld)1/k * dp[es[j].s];
                }
            } else {
                // we precomputed the probabilities
                assert(sz(p[k]) == k);
                F0R(j, k) {
                    dp[i] += (ld)p[k][j]*dp[es[j].s];
                }
            }
            
            dbg(i, dp[i]);
        }
        cout.precision(12);
        cout << fixed << dp[1] << nl;
    }
    return 0;
}
