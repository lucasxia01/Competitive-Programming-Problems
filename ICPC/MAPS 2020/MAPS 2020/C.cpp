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

const int MX = 1e5+5;
pi cost[MX]; // cost and highest bit
bool canReachZero[MX];
vi edges[MX], revE[MX];
int m;

void solve() {
    set<pair<pi, pi> > q; // cost, highest bit, remainder mod m, parent node
    q.insert({{1,0}, {1,1}});
    int bestAns = -1;
    while (!q.empty()) {
        pair<pi, pi> cur = *q.begin();
        int curC = cur.f.f;
        int highBit = cur.f.s;
        int curN = cur.s.f;
        int parN = cur.s.s;
        q.erase(q.begin());
        if (cost[curN].f && cost[curN] < cur.f) continue;
        edges[parN].pb(curN);
        revE[curN].pb(parN);
        // cout << highBit << " " << parN << " " << curN << " " << curC << endl;
        if (cost[curN].f) continue;
        cost[curN] = cur.f;
        if (curN == 0) {
            // cout << cur.f.f << endl;
            bestAns = highBit;
            break;
        }
        q.insert({{curC+1, highBit+1}, {(2*curN+1)%m, curN}});
        q.insert({{curC, highBit+1}, {(2*curN)%m, curN}});
    }
    assert(bestAns != -1);
    // we get all the nodes that can reach 0 in the minimum number of steps
    canReachZero[0] = 1;
    queue<int> s; s.push(0);
    while (!s.empty()) {
        int cur = s.front(); s.pop();
        // cout << cur << endl;
        trav(a, revE[cur]) {
            if (!canReachZero[a]) {
                canReachZero[a] = 1;
                s.push(a);
            }
        }
    }
    // build the solution bit by bit
    vi ans; ans.pb(bestAns);
    int cur = 1;
    F0Rd(i, bestAns) {
        // cout << cur << " " << (cur*2)%m << " " << canReachZero[(cur*2)%m] << endl;
        if (find(edges[cur].begin(), edges[cur].end(), (cur*2)%m) != edges[cur].end() && canReachZero[(cur*2)%m]) {
            cur = (cur*2)%m;
        } else {
            ans.pb(i);
            cur = (cur*2+1)%m;
        }
    }
    F0Rd(i, sz(ans)) cout << ans[i] << " ";
    cout << '\n';
    
}

void bfs2() {
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N;
    cin >> N;
    while (N--) {
        cin >> m;
        if (m == 1) {
            cout << 0 << endl;
            continue;
        }
        memset(cost, 0, sizeof(cost));
        memset(canReachZero, 0, MX);
        F0R(i, MX) edges[i].clear();
        F0R(i, MX) revE[i].clear();
        solve();
    }
    
    return 0;
}
