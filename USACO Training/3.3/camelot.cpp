/*
ID: lucasxi1
TASK: camelot
LANG: C++                 
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
#define int ll

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

int dx[8] = {2, 2, 1, -1, -2, -2, -1, 1};
int dy[8] = {-1, 1, 2, 2, 1, -1, -2, -2};

signed main() {
    freopen("camelot.in", "r", stdin);
    freopen("camelot.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int r, c; cin >> c >> r;
    int dp[r][c][r][c];
    F0R(i, r) F0R(j, c) {
        F0R(ii, r) F0R(jj, c) dp[i][j][ii][jj] = INF;
        queue<pair<pi, int> > q;
        q.push({{i, j}, 0});
        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            int x = cur.f.f, y = cur.f.s;
            if (dp[i][j][x][y] != INF) continue;
            dp[i][j][x][y] = cur.s;
            F0R(d, 8) {
                int nx = x+dx[d], ny = y+dy[d];
                if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
                q.push({{nx, ny}, cur.s+1});
            }
        }

    }
    char x; int y; cin >> x >> y;
    pi K = {x-'A', --y};
    vpi knights;
    while (cin >> x) {
        cin >> y;
        knights.pb({x-'A', --y});
    }
    int ans = INF;
    F0R(i, r) F0R(j, c) {
        // choose a dude to travel
        int sum = 0;
        trav(k, knights) sum += dp[k.f][k.s][i][j];
        int s = sum + max(abs(K.f-i), abs(K.s-j));
        ckmin(ans, s);
        trav(k, knights) {
            int tmp = sum - dp[k.f][k.s][i][j];
            // now pick a spot around K
            FOR(dx, -5, 5) {
                FOR(dy, -5, 5) {
                    int nx = K.f+dx, ny = K.s+dy;
                    if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
                    int cur = tmp + max(abs(dx), abs(dy)) + dp[k.f][k.s][nx][ny] + dp[nx][ny][i][j];
                    ckmin(ans, cur);
                }
            }
        }
    }
    cout << ans << nl;
    return 0;
}
