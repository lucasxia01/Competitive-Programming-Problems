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

const int N = 500;

vector<int> gr[N];
  
// Function to add edge
void Add_edge(int x, int y)
{
    gr[x].push_back(y);
    gr[y].push_back(x);
}
  
// Function to find the length of
// the shortest cycle in the graph
int shortest_cycle(int n)
{
    // To store length of the shortest cycle
    int ans = INF;
  
    // For all vertices
    for (int i = 0; i < n; i++) {
  
        // Make distance maximum
        vector<int> dist(n, (int)(1e9));
  
        // Take a imaginary parent
        vector<int> par(n, -1);
  
        // Distance of source to source is 0
        dist[i] = 0;
        queue<int> q;
  
        // Push the source element
        q.push(i);
  
        // Continue until queue is not empty
        while (!q.empty()) {
  
            // Take the first element
            int x = q.front();
            q.pop();
  
            // Traverse for all it's childs
            for (int child : gr[x]) {
  
                // If it is not visited yet
                if (dist[child] == (int)(1e9)) {
  
                    // Increase distance by 1
                    dist[child] = 1 + dist[x];
  
                    // Change parent
                    par[child] = x;
  
                    // Push into the queue
                    q.push(child);
                }
  
                // If it is already visited
                else if (par[x] != child and par[child] != x)
                    ans = min(ans, dist[x] + dist[child] + 1);
            }
        }
    }
  
    // If graph contains no cycle
    if (ans == INF)
        return -1;
  
    // If graph contains cycle
    else
        return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    int v, u;
    F0R(i, m) {
        cin >> v >> u;
        gr[v].pb(u);
        gr[u].pb(v);
    }
//    int ans = INF;
//    F0R(i, n) {
//        queue<int> q; q.push(i);
//        int d[n]; F0R(i, n) d[i] = -1;
//        d[i] = 0;
//        bool done = false;
//        while (!q.empty()) {
//            v = q.front(); q.pop();
////             cout << v << " ";
//            F0R(j, n) {
//                if (gr[v][j] && d[j] > 0) {
//                    ckmin(ans, d[v]+d[j]+1);
//                    done = true;
//                    break;
//                }
//                if (gr[v][j] && d[j] == -1) {
//                    q.push(j);
//                    d[j] = d[v]+1;
//                }
//            }
//            if (done) break;
//        } //cout << nl;
//    }
    int ans = shortest_cycle(n);
    if (ans == -1) cout << "impossible" << nl;
    else cout << ans << nl;
    return 0;
}
