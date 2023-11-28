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
    int t = 1; 
    cin >> t;
    while (t--) {
        int n, m, k; cin >> n >> m >> k;
        vector<array<int, 3> > v;
        pi a[m];
        F0R(i, m) {
            int l, r; cin >> l >> r;
            v.pb({l, 1, i});
            v.pb({r+1, 0, i});
            a[i] = {l, r+1};
        }
        sort(all(v));
        // find the k latest things that are active in each thing
        map<vector<pi>, int> dp[n+2][k+1];
        dp[1][0][{}] = 0;
        set<int> cur;
        int ptr = 0;
        FOR(i, 1, n) {
            int ii = i+1;
            // clear i
            while (ptr < 2*m && v[ptr][0] == i) {
                if (v[ptr][1]==0) cur.erase(v[ptr][2]);
                else cur.insert(v[ptr][2]);
                ptr++;
            }
            vector<pi> new_s2;
            if (sz(cur) <= k) {
                trav(p, cur) {
                    new_s2.pb({a[p].s, p});
                }
            }
            dbg(i, sz(cur));
            F0R(j, k+1) {
                // do nothing
                dbg(i, j, sz(dp[i][j]));
                assert(sz(dp[i][j]) <= k+1);
                trav(s, dp[i][j]) {
                    // dbg(i, j, s.s, sz(cur));
                    // trav(p, s.f) {
                    //     cerr << p.s << " " << p.f << ' ';
                    // } cerr<< nl;
                    assert(sz(s.f) <= k);
                    // update to see if its been passed
                    vpi new_s;
                    trav(p, s.f) {
                        if (p.f < i+1) continue;
                        new_s.pb(p);
                    }
                    // trav(p, new_s) {
                    //     cerr << p.s << " " << p.f << ' ';
                    // } cerr<< nl;
                    int val = (sz(new_s) == sz(cur));
                    ckmax(dp[ii][j][new_s], s.s+val);

                    // try to remove everything
                    
                    int cost = sz(cur)-sz(new_s);
                    if (cost+j > k) continue;
                    ckmax(dp[ii][j+cost][new_s2], s.s+1);
                }
            }
            F0R(j, k+1) dp[i][j].clear();
        }
        int ans = 0;
        F0R(j, k+1) {
            trav(s, dp[n+1][j]) {
                ckmax(ans, s.s);
            }
        }
        cout << ans << nl;
    }
    return 0;
}
