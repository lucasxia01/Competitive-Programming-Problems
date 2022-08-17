#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <chrono>
#include <cassert>

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

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 400+5;

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

struct Pos {
    int x, y, dir, dist;
    void pr() {
        cout << x << " " << y << " " << dir << " " << dist << nl;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("straight.in", "r", stdin);
//    freopen("straight.out", "w", stdout);
    int n, m; cin >> m >> n;
    string g[2*m-1];
    getline(cin, g[0]);
    F0R(i, 2*m-1) getline(cin, g[i]);
    int dist[m][n]; F0R(i, m) F0R(j, n) dist[i][j] = INF;
    dist[0][n-1] = 0;
    queue<pi> q; q.push({0, n-1});
    while (!q.empty()) {
        pi cur = q.front(); q.pop();
        F0R(d, 4) {
            int nx = 2*cur.f+dx[d], ny = 2*cur.s+dy[d];
            int nnx = 2*cur.f+2*dx[d], nny = 2*cur.s+2*dy[d];
            if (nx < 0 || nx >= 2*m-1 || ny < 0 || ny >= 2*n-1 || dist[nnx/2][nny/2] != INF || g[nx][ny] == ' ') continue;
            dist[nnx/2][nny/2] = dist[cur.f][cur.s]+1;
            q.push({nnx/2, nny/2});
        }
    }
    int total = dist[m-1][0];
    queue<Pos> pos;
    pos.push({m-1, 0, 3, 0});
    pos.push({m-1, 0, 0, 0});
    Pos vis[m][n][4]; F0R(i, m) F0R(j, n) F0R(k, 4) vis[i][j][k] = {-1, -1, -1, -1};
    vis[m-1][0][3] = {m-1, 0, 3, 0};
    vis[m-1][0][0] = {m-1, 0, 0, 0};
    Pos end;
    while (!pos.empty()) {
        Pos cur = pos.front(); pos.pop();
//        cur.pr();
        if (cur.x == 0 && cur.y == n-1) {
            end = cur;
            break;
        }
        int d = cur.dir;
        int nx = 2*cur.x+dx[d], ny = 2*cur.y+dy[d];
        int nnx = 2*cur.x+2*dx[d], nny = 2*cur.y+2*dy[d];
        if (nx < 0 || nx >= 2*m-1 || ny < 0 || ny >= 2*n-1 || vis[nnx/2][nny/2][d].x != -1 || g[nx][ny] == ' ' || cur.dist+1+dist[nnx/2][nny/2] != total) {
            if (cur.x == m-1 && cur.y == 0) continue;
            F0R(dd, 4) {
                if (dd == cur.dir || dd == (cur.dir+2)%4) continue;
                nx = 2*cur.x+dx[dd]; ny = 2*cur.y+dy[dd];
                nnx = 2*cur.x+2*dx[dd]; nny = 2*cur.y+2*dy[dd];
                if (nx < 0 || nx >= 2*m-1 || ny < 0 || ny >= 2*n-1 || vis[nnx/2][nny/2][dd].x != -1 || g[nx][ny] == ' '
                    || cur.dist+1+dist[nnx/2][nny/2] != total) continue;
                pos.push({nnx/2, nny/2, dd, cur.dist+1});
                vis[nnx/2][nny/2][dd] = cur;
            }
        } else {
            pos.push({nnx/2, nny/2, d, cur.dist+1});
            vis[nnx/2][nny/2][d] = cur;
        }
    }
//    cout << nl;
    string ans = "";
    while (end.x != m-1 || end.y != 0) {
//        end.pr();
        Pos prev = vis[end.x][end.y][end.dir];
        if (prev.dir == end.dir) ans += 'F';
        else if ((prev.dir+1)%4 == end.dir) ans += 'R';
        else if ((prev.dir+3)%4 == end.dir) ans += 'L';
        else assert(0);
        assert(prev.dist+1 == end.dist);
        end = prev;
    }
//    end.pr();
    cout << "NE"[end.dir==0] << nl;
    reverse(ans.begin(), ans.end());
    ans = ans.substr(1);
    cout << ans << nl;
    return 0;
}

//4 4
//+-+ +-+
//| |   |
//+ +-+-+
//|   |
//+-+-+-+
//|     |
//+-+-+-+
