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
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

int n, m;
string g[50];
bool vis[50][50];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

struct box {
    int minx = 100, miny = 100, maxx = -1, maxy = -1;
    void upd(int x, int y) {
        ckmin(minx, x);
        ckmin(miny, y);
        ckmax(maxx, x);
        ckmax(maxy, y);
    }
    void reset() {
        minx = 100, miny = 100, maxx = -1, maxy = -1;
    }

};

box cur;

void dfs(int x, int y) {
    if (x < 0 || y < 0 || x >= n || y >= m || vis[x][y] || g[x][y] == '.') return;
    vis[x][y] = 1;
    cur.upd(x, y);
    F0R(d, 4) {
        int nx = x+dx[d];
        int ny = y+dy[d];
        dfs(nx, ny);
    }
}

void fillin() {
    // fill in x
    F0R(i, n) {
        int a = 100, b = -1;
        F0R (j, m) {
            if (g[i][j] ==  '#') {
                ckmin(a, j);
                ckmax(b, j);
            }
        }
        if (a < 100 && a != b) {
            FOR(j, a, b) {
                g[i][j] = '#';
            }
        }
    }
    // y
    F0R(i, m) {
        int a = 100, b = -1;
        F0R (j, n) {
            if (g[j][i] ==  '#') {
                ckmin(a, j);
                ckmax(b, j);
            }
        }
        if (a < 100 && a != b) {
            FOR(j, a, b) {
                g[j][i] = '#';
            }
        }
    }
}

void walk(pi a, pi b) {
    dbg(a.f, a.s, b.f, b.s);
    FOR(i, min(a.f, b.f), max(a.f, b.f)) {
        g[i][a.s] = '#';
    }
    FOR(i, min(a.s, b.s), max(a.s, b.s)) {
        g[b.f][i] = '#';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        F0R(i, n) cin >> g[i];
        F0R(i, n) F0R(j, m) vis[i][j] = 0;
        // now dfs
        vector<box> v;
        F0R(i, n) F0R(j, m) {
            if (vis[i][j] || g[i][j] == '.') continue;
            dbg(i, j);
            cur.reset();
            dfs(i, j);
            v.pb(cur);
        }
        dbg("hi");
        if (v[0].maxx < v[1].minx && v[0].maxy < v[1].miny) {
            walk({v[0].maxx, v[0].maxy}, {v[1].minx, v[1].miny});
        } else if (v[0].maxx < v[1].minx && v[0].miny > v[1].maxy) {
            walk({v[0].maxx, v[0].miny}, {v[1].minx, v[1].maxy});
        } else if (v[0].minx > v[1].maxx && v[0].maxy < v[1].miny) {
            walk({v[0].minx, v[0].maxy}, {v[1].maxx, v[1].miny});
        } else if (v[0].maxx < v[1].minx && v[0].miny > v[1].maxy) {
            walk({v[0].minx, v[0].miny}, {v[1].maxx, v[1].maxy});
        }
        dbg("after walk");
        while (1) {
            string g2[n];
            F0R(i, n) g2[i] = g[i];
            fillin();
            bool change = 0;
            F0R(i, n) if (g2[i] != g[i]) change = 1;
            if (!change) break;
        }
        F0R(i, n) {
            F0R(j, m) cout << g[i][j];
            cout << nl;
        }
    }
    return 0;
}
