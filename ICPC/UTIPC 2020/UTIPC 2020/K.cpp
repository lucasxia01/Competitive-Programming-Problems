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

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

const int MX = 202;
int n;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
bool vis[MX][MX][1<<10];
int sX, sY, eX, eY;
string m[MX];

struct State {
    int x, y, mask, dist;
};
void bfs() {
    queue<State> q;
    q.push({sX, sY, 0, 0});
    while (!q.empty()) {
        auto [x, y, mask, dist] = q.front(); q.pop();
        // cout << x << " " << y << " " << dist << endl;
        if (vis[x][y][mask]) continue;
        if (x == eX && y == eY) {
            cout << dist << endl;
            return;
        }
        if (m[x][y] >= 'A' && m[x][y] <= 'J') {
            if ((mask&(1<<(m[x][y]-'A'))) == 0) continue;
        }
        vis[x][y][mask] = 1;
        F0R(d, 4) {
            int nX = x+dx[d], nY = y+dy[d];
            if (nX < 0 || nX >= n || nY < 0 || nY >= n || m[nX][nY] == '#') continue;
            if (m[nX][nY] >= 'a' && m[nX][nY] <= 'j')
                q.push({nX, nY, mask|(1<<(m[nX][nY]-'a')), dist+1});
            else q.push({nX, nY, mask, dist+1});
        }
    }
    cout << "IMPOSSIBLE" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    F0R(i, n) cin >> m[i];
    F0R(i, n) F0R(j, n) {
        if (m[i][j] == '@') sX = i, sY = j;
        if (m[i][j] == '$') eX = i, eY = j;
    }
    bfs();
    return 0;
}
