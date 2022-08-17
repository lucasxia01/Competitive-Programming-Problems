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
#include <climits>

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

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 2005;

int dx[2] = {0, 1};
int dy[2] = {1, 0};

string a[MX]; 
int vis[MX][MX];
int n, k;

int nxtX[MX][MX];
int prevX[MX][MX];
int nxtY[MX][MX];
int prevY[MX][MX];

void del(int nx, int y) {
    // dbg("delete", nx, y);
    if (prevX[nx][y] >= 0) nxtX[prevX[nx][y]][y] = nxtX[nx][y];
    if (nxtX[nx][y] < n) prevX[nxtX[nx][y]][y] = prevX[nx][y];
    if (prevY[nx][y] >= 0) nxtY[nx][prevY[nx][y]] = nxtY[nx][y];
    if (nxtY[nx][y] < n) prevY[nx][nxtY[nx][y]] = prevY[nx][y];
}

void bfs() {
    queue<pi> q; q.push({0, 0}); vis[0][0] = 0;
    while (!q.empty()) {
        pi cur = q.front(); q.pop();
        int x = cur.f, y = cur.s;
        // dbg("cur", cur.f, cur.s, vis[cur.f][cur.s]);
        int nx = x;
        while (1) {
            nx = nxtX[nx][y];
            // dbg("nxtX", nx, y);
            if (nx < 0 || nx >= n || nx-x > k) break;
            if (vis[nx][y] != -1) continue;
            q.push({nx, y});
            vis[nx][y] = vis[x][y]+1;
            del(nx, y);
        }
        // dbg("y time", x, y);
        int ny = y;
        while (1) {
            // dbg(x, ny);
            ny = nxtY[x][ny];
            // dbg("nxtY", x, ny);
            if (ny < 0 || ny >= n || ny-y > k) break;
            if (vis[x][ny] != -1) continue;
            q.push({x, ny});
            vis[x][ny] = vis[x][y]+1;
            del(x, ny);
        }
        
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    F0R(i, n) cin >> a[i];
    F0R(i, n) F0R(j, n) vis[i][j] = -1;
    F0R(i, n) F0R(j, n) {
        prevX[i][j] = i-1;
        nxtX[i][j] = i+1;
        prevY[i][j] = j-1;
        nxtY[i][j] = j+1;
    }
    F0R(i, n) F0R(j, n) if (a[i][j] == '#') del(i, j);
    dbg(nxtX[2][0], prevX[2][0]);
    bfs();
    int ans = vis[n-1][n-1];
    cout << ans << nl;
    return 0;
}
