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

int gr[N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; scanf("%d",&t);
    F0R(T, t) {
        int n, m; scanf("%d%d",&n,&m);
        int v, u;
        F0R(i, m) {
            scanf("%d%d",&u,&v);
            gr[v][u] = gr[u][v] = 1;
        }
        int ans = INF;
        F0R(i, n) {
            queue<int> q; q.push(i);
            int d[n], par[n]; F0R(i, n) d[i] = par[i] = -1;
            d[i] = 0;
            while (!q.empty()) {
                v = q.front(); q.pop();
                F0R(j, n) {
                    if (gr[v][j] && d[j] > 0 && par[v] != j) {
                        ckmin(ans, d[v]+d[j]+1);
                    } else if (gr[v][j] && d[j] == -1) {
                        q.push(j);
                        d[j] = d[v]+1;
                        par[j] = v;
                    }
                }
            }
        }
        printf("Case %d: ", T+1);
        if (ans == INF) printf("impossible\n");
        else printf("%d\n", ans);
    }
    return 0;
}
