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

const int MX = 3e3+5;

int n, m;
string a[MX];
int vis[MX][MX], ans[MX][MX];
set<pi> v;
int cnt = 0;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m) return;
    else if (a[x][y] == 'B') return;
    else if (a[x][y] == '.') {
        v.insert({x, y});
        return;
    } else if (vis[x][y]) return;
    vis[x][y] = 1;
    cnt++;
    F0R(d, 4) {
        int nx = x+dx[d];
        int ny = y+dy[d];
        dfs(nx, ny);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    FOR(tt, 1, t) {
        cout << "Case #" << tt << ": ";
        cin >> n >> m;
        F0R(i, n) cin >> a[i];
        // for each white component, find which ones it depends on
        int hi = 0;
        F0R(i, n) F0R(j, m) vis[i][j] = ans[i][j] = 0;
        F0R(i, n) F0R(j, m) {
            if (a[i][j] == 'W' && !vis[i][j]) {
                v.clear();
                cnt = 0;
                dfs(i, j);
                // dbg(i, j, sz(v), cnt);
                // trav(p, v) {
                //     dbg(p.f, p.s);
                // }
                if (sz(v) == 1) {
                    pi p = *v.begin();
                    // dependence on this thing
                    ans[p.f][p.s] += cnt;
                    ckmax(hi, ans[p.f][p.s]);
                }
            } 
        }
        cout << (hi?"YES":"NO") << nl;
    }
    return 0;
}
