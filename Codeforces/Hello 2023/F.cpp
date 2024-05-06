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

const int MX = 2e5+5;

vi gr[MX];
int a[MX];

pair<bool, vpi> dp[MX][32]; // for node and value, give the children and their values

pi solve(int v) {
    int cnt = 1;
    int x = a[v];
    int m = sz(gr[v]);
    int knap[m+1][32];
    F0R(j, m+1) F0R(i, 32) knap[j][i] = -1;
    knap[0][0] = 0;
    int i = 0;
    trav(u, gr[v]) {
        pi ret = solve(u);
        F0R(j, 32) {
            if (knap[i][j] == -1) continue;
            F0R(k, 32) {
                if (dp[u][k].f) {
                    knap[i+1][j^k] = j;
                }
            }
        }
        i++;
        cnt += ret.f;
        x ^= ret.s;
    }
    // set the dp values
    F0R(j, 32) {
        if (knap[m][j] == -1) continue;
        dbg(v+1, j);
        int cur = j;
        dp[v][j].f = 1;
        FORd(i, 1, m) {
            dbg(v+1, j, gr[v][i-1]+1, cur, (cur^knap[i][cur]));
            dp[v][j].s.pb({gr[v][i-1], (cur^knap[i][cur])});
            cur = knap[i][cur];
        }
    }
    if (cnt%2 == 0) {
        dp[v][x] = {1, {{v, -1}}};
    }
    return {cnt, x};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    F0R(i, n) cin >> a[i];
    F0R(i, n-1) {
        int x; cin >> x; x--;
        gr[x].pb(i+1);
    }
    pi ret = solve(0);
    dbg("want", ret.s);
    if (dp[0][ret.s].f) {
        vi ans;
        stack<pi> s; s.push({0, ret.s});
        while (!s.empty()) {
            pi cur = s.top(); s.pop();
            dbg(cur.f+1, cur.s);
            if (sz(dp[cur.f][cur.s].s) == 1 && dp[cur.f][cur.s].s[0].s == -1) {
                ans.pb(cur.f);
                continue;
            }
            trav(t, dp[cur.f][cur.s].s) {
                s.push(t);
            }
        }
        ans.pb(0);
        cout << sz(ans) << nl;
        trav(aa, ans) cout << aa+1 << " ";
        cout << nl;

    } else {
        cout << -1 << nl;
    }
    return 0;
}
