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

const int MAX_N = 100011;
const ll INF = (1LL<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int vis[1010][10010];
struct Node {
    int a, b, c;
    bool operator < (const Node& o) const {
        return (a > o.a || (a == o.a && b > o.b));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, g, r;
    cin >> n >> m;
    int d[m];
    F0R(i, m) cin >> d[i];
    sort(d, d+m);
    cin >> g >> r;
    memset(vis, INF, sizeof(vis));
    priority_queue<Node> q; // states are multiple of g, and mod g, and node
    q.push({0, 0, 0});
    vis[0][0] = 0;
    while (!q.empty()) {
        auto [a, b, c] = q.top(); q.pop();
        // cout << cur.f << " " << cur.s.f << " " << cur.s.s << endl;
        if (vis[b][c] < a) continue;
        if (c == m-1) {
            int ans = a*(g+r) + b;
            if (b == 0) ans -= r;
            cout << ans << endl;
            return 0;
        }
        // left
        int newTime;
        if (c > 0 && (newTime=(b+d[c]-d[c-1])) <= g) {
            newTime = (newTime==g) ? 0 : newTime;
            int t = a+(!newTime);
            if (ckmin(vis[newTime][c-1], t)) {
                q.push({t, newTime, c-1});
            }
        }
        if ((newTime=(b+d[c+1]-d[c])) <= g) {
            newTime = (newTime==g) ? 0 : newTime;
            int t = a+(!newTime);
            if (ckmin(vis[newTime][c+1], t)) {
                q.push({t, newTime, c+1});
            }
        }
    }
    cout << -1 << endl;
    return 0;
}
