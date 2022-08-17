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
 
const int MX = 1005;
int n, m;
int a[MX][MX];
int vis[MX][MX];
vector<pair<pi, int> > ans;
 
bool check(int x, int y) {
    if (x < 0 || x >= n-1 || y < 0 || y >= m-1) return 0;
    int c = 0;
    F0R(i, 2) F0R(j, 2) if (a[x+i][y+j] != 0) c = a[x+i][y+j];
    F0R(i, 2) F0R(j, 2) if (a[x+i][y+j] != 0 && a[x+i][y+j] != c) return 0;
    return 1;
}
 
void dfs(int x, int y) {
    if (vis[x][y]) return;
    int c = 0;
    F0R(i, 2) F0R(j, 2) if (a[x+i][y+j] != 0) c = a[x+i][y+j];
    ans.pb({{x, y}, c});
    F0R(i, 2) F0R(j, 2) a[x+i][y+j] = 0;
    vis[x][y] = 1;
    if (check(x-1, y-1)) dfs(x-1, y-1);
    if (check(x-1, y)) dfs(x-1, y);
    if (check(x-1, y+1)) dfs(x-1, y+1);
 
    if (check(x, y-1)) dfs(x, y-1);
    if (check(x, y+1)) dfs(x, y+1);
 
    if (check(x+1, y-1)) dfs(x+1, y-1);
    if (check(x+1, y)) dfs(x+1, y);
    if (check(x+1, y+1)) dfs(x+1, y+1);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    F0R(i, n) F0R(j, m) cin >> a[i][j];
    F0R(i, n-1) F0R(j, m-1) {
        bool ok = 1;
        F0R(ii, 2) F0R(jj, 2) if (a[i+ii][j+jj] != a[i][j]) ok = 0;
        if (ok) {
            dfs(i, j);            
        }
    }
    if (sz(ans) != (n-1)*(m-1)) cout << -1 << nl;
    else {
        cout << sz(ans) << nl;
        reverse(all(ans));
        trav(aa, ans) {
            if (aa.s == 0) aa.s = 1;
            cout << aa.f.f+1 << " " << aa.f.s+1 << " " << aa.s << nl;
        }
    }
    return 0;
}
