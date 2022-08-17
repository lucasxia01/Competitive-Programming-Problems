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
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct State {
    char x; int y;
    vector<pair<char, int> > steps;
};

const int MX = 1<<20;
int dx[4] = {1, 1, -1, -1}, dy[4] = {1, -1, 1, -1};
int vis[8][9];

void bfs(char sX, int sY, char eX, int eY) {
    queue<State> q;
    vector<pair<char, int> > temp = {{sX, sY}};
    State temps; temps.x = sX; temps.y = sY; temps.steps = temp;
    q.push(temps);
    while (!q.empty()) {
        State p = q.front(); q.pop();
//        dbg(p.x, p.y);
        if (p.x==eX && p.y==eY) {
            cout << sz(p.steps)-1 << " ";
            trav(s, p.steps) cout << s.f << " " << s.s << " "; cout << nl;
            return;
        }
        F0R(k, 10) {
            F0R(d, 4) {
                char nx = p.x+k*dx[d]; int ny = p.y+k*dy[d];
                if (nx < 'A' || nx > 'H' || ny < 1 || ny > 8) continue;
                if (vis[nx-'A'][ny]) continue;
                vis[nx-'A'][ny] = 1;
                State np; np.x = nx; np.y = ny;
                np.steps = p.steps;
                np.steps.pb({nx, ny});
                q.push(np);
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    F0R(i, n) {
        char x0, x1;
        int y0, y1;
        cin >> x0 >> y0 >> x1 >> y1;
//        dbg(x0, y0, x1, y1);
        F0R(j, 8) F0R(k, 9) vis[j][k] = 0;
        if ((x0-x1 + y0-y1)%2) {
            cout << "Impossible" << nl;
            continue;
        }
        bfs(x0, y0, x1, y1);
        
    }
    
    return 0;
}
