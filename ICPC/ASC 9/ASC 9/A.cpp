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

const int MX = 10;

const int SZ = 1<<(MX-1);

int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int vis[12*SZ+1][3*SZ+1]; // 0 is not vis, >0 is vis but not final, -1 is final vis
int n;
int a[MX];

int gcd(int c, int b) {
    if (c < b) return gcd(b, c);
    if (b == 0) return c;
    return gcd(b, c%b);
}

void bfs(int i) {
    int step = SZ/(1<<i);
    queue<pi> qPos;
    pi end = {SZ*i+SZ, SZ}, start = {SZ*a[i]+SZ, 2*SZ};
    qPos.push(start);
    vpi path;
    while (!qPos.empty()) {
        pi cur = qPos.front(); qPos.pop();
        F0R(d, 4) {
            pi nxt = {cur.f+step*dx[d], cur.s+step*dy[d]};
            if (nxt.f < 0 || nxt.f > 12*SZ || nxt.s < 0 || nxt.s > 3*SZ) continue;
            if (nxt == end) {
                int curx = end.f, cury = end.s;
                int count = 0, dir = -1;
                vis[nxt.f][nxt.s] = 4*(i+1)+d;
                while (curx != start.f || cury != start.s) {
                    if (count%step==0) {
                        assert(vis[curx][cury]/4 == i+1);
                        if (dir != ((vis[curx][cury]%4)^1)) path.pb({curx, cury});
                        dir = (vis[curx][cury]%4)^1;
                    }
                    vis[curx][cury] = -1;
                    curx += dx[dir]; cury += dy[dir];
                    count++;
                }
                path.pb({start});
                cout << sz(path)-1 << nl;
                trav(p, path) {
                    int x = p.f, y = p.s;
                    x -= SZ; y -= SZ;
                    assert(x%step == 0 && y%step == 0);
                    x /= step; y /= step;
                    int t = SZ/step;
                    int gx = gcd(abs(x), t), gy = gcd(abs(y), t);
                    cout << x/gx << "/" << t/gx << " " << y/gy << "/" << t/gy << nl;
                }
                return;
            }
            if (vis[nxt.f][nxt.s] == -1 || vis[nxt.f][nxt.s]/4 == i+1) continue;
            vis[nxt.f][nxt.s] = 4*(i+1)+d;
            qPos.push(nxt);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("chip.in", "r", stdin);
//    freopen("chip.out", "w", stdout);
    cin >> n;
    F0R(i, n) {
        cin >> a[i];
        a[i]--;
        vis[SZ*i+SZ][SZ] = vis[SZ*i+SZ][2*SZ] = -1;
    }
    F0R(i, n) bfs(i);
    return 0;
}
