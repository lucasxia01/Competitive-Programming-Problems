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

const int MX = 1001*1001+5;

int dx[6] = {1, -1, 0, 0, 1, -1}, dy[6] = {0, 0, 1, -1, -1, -1};
int par[MX], sze[MX];

int find(int p) {
    return (p==par[p]?p:par[p]=find(par[p]));
}
void merge(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (sze[a] < sze[b]) swap(a, b);
    sze[a] += sze[b];
    par[b] = a;
}

int convert(int x, int y) {
    if (x < -500 || x > 500 || y < -500 || y > 500) return 0;
    return 1001*(x+500)+(y+501);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("islands.in", "r", stdin);
//    freopen("islands.out", "w", stdout);
    int n, s;
    cin >> n >> s;
    int x, y;
    // conversion from coord to index is 1001*(f+500)+(s+500)
    F0R(i, n) {
        cin >> x >> y;
        int total = 0;
        int idx = convert(x, y);
        if (sze[idx]) continue;
        set<int> isls;
        F0R(i, 6) {
            int nx = x+dx[i], ny = y+dy[i];
            if (x%2) nx = x-dx[i], ny = y-dy[i];
            int root = find(convert(nx, ny));
            isls.insert(root);
        }
        trav(v, isls) total += sze[v];
        if (total+1 <= s) {
            sze[idx] = 1;
            par[idx] = idx;
            F0R(i, 6) {
                int nx = x+dx[i], ny = y+dy[i];
                if (x%2) nx = x-dx[i], ny = y-dy[i];
                int root = find(convert(nx, ny));
                if (root) merge(root, idx);
            }
        }
    }
    vi ans;
    FOR(i, 1, MX-1) {
        if (par[i] == i) ans.pb(sze[i]);
    }
    cout << sz(ans) << nl;
    sort(ans.begin(), ans.end());
    trav(a, ans) cout << a << " "; cout << nl;
    
    return 0;
}
