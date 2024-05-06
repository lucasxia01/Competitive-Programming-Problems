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

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        string a[n]; F0R(i, n) cin >> a[i];
        // determine the type by bfs-ing from V
        int sx, sy;
        F0R(i, n) F0R(j, m) {
            if (a[i][j] == 'V') {
                sx = i, sy = j;
                break;
            }
        }
        int dist[n][m];
        F0R(i, n) F0R(j, m) dist[i][j] = -1;
        vpi exits;
        int ans = 0;
        queue<pi> q; q.push({sx, sy});
        dist[sx][sy] = 0;
        while (!q.empty()) {
            pi cur = q.front(); q.pop();
            int x = cur.f, y = cur.s;
            if (x == 0 || x == n-1 || y == 0 || y == m-1) exits.pb({x, y});
            F0R(i, 4) {
                int nx = x+dx[i], ny = y+dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (dist[nx][ny] != -1) continue;
                if (a[nx][ny] == '#') continue;
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
        F0R(i, n) F0R(j, m) {
            if (a[i][j] == '.' || a[i][j] == 'V') ans++;
        }
        int total = ans;
        if (sz(exits) == 0) {
            cout << ans-1 << nl;
            continue;
        } else if (sz(exits) == 1) {
            cout << ans-1-dist[exits[0].f][exits[0].s] << nl;
            continue;
        }
        // dbg(sz(exits));
        // trav(e, exits) {
        //     dbg(e.f, e.s, dist[e.f][e.s]);
        // }
        // figure out where to split!
        vpi dist2[n][m];
        // F0R(i, n) F0R(j, m) dist2[i][j] = {-1, -1};
        queue<pi> q2;
        int idx = 0;
        trav(e, exits) {
            dist2[e.f][e.s].pb({1, idx});
            q2.push({e.f, e.s});
            idx++;
        }
        while (!q2.empty()) {
            pi cur = q2.front(); q2.pop();
            int x = cur.f, y = cur.s;
            dbg(x, y, dist2[x][y][0].f, dist2[x][y][0].s);
            F0R(i, 4) {
                int nx = x+dx[i], ny = y+dy[i];
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (a[nx][ny] == '#') continue;
                if (sz(dist2[nx][ny]) == 0) { // we can just replace it
                    trav(p, dist2[x][y]) {
                        dist2[nx][ny].pb({p.f+1, p.s});
                    }
                    q2.push({nx, ny});
                } else if (sz(dist2[nx][ny]) == 1) {
                    dbg(nx, ny, "already reached once");
                    int idx = dist2[nx][ny][0].s;
                    bool ok = 0;
                    trav(p, dist2[x][y]) {
                        if (idx == p.s) continue;
                        dist2[nx][ny].pb({p.f+1, p.s});
                        ok = 1;
                    }
                    if (sz(dist2[nx][ny]) == 3) {
                        dist2[nx][ny].pop_back();
                    }
                    if (ok) q2.push({nx, ny});
                }

            }
        }
        int path = 1e9;
        F0R(i, n) F0R(j, m) {
            if (sz(dist2[i][j]) == 2) {
                dbg(i, j, dist[i][j], dist2[i][j][0].f, dist2[i][j][1].f);
                ckmin(path, dist[i][j]+dist2[i][j][0].f+dist2[i][j][1].f-1);
            }
        }
        cout << total-path << nl;
    }
    return 0;
}
