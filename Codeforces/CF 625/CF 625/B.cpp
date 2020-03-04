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

const int MAX_N = 200011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

int dist[MAX_N];
vi e[MAX_N], revE[MAX_N];
int t;
void bfs() {
    queue<int> q;
    dist[t] = 0;
    q.push(t);
    while (!q.empty()) {
        trav(a, revE[q.front()]) {
            if (dist[a] == INF) {
                dist[a] = dist[q.front()]+1;
                q.push(a);
            }
        }
        q.pop();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, u, v;
    cin >> n >> m;
    F0R(i, m) {
        cin >> u >> v;
        e[u].pb(v);
        revE[v].pb(u);
    }
    F0R(i, n) dist[i+1] = INF;
    int k;
    cin >> k;
    int p[k];
    F0R(i, k) cin >> p[i];
    t = p[k-1];
    bfs();
    int minAns = 0, maxAns = 0;
    F0R(i, k-1) {
        if (dist[p[i]] != dist[p[i+1]]+1) {
            minAns++;
            maxAns++;
        } else {
            trav(a, e[p[i]]) {
                if (a != p[i+1] && dist[a]+1 == dist[p[i]]) {
                    maxAns++;
                    break;
                }
            }
        }
    }
    cout << minAns << " " << maxAns << endl;
    return 0;
}
