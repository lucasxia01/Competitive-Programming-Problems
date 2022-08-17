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

const int MX = 1e5+5;
vi gr[MX];
int ans[MX];

void dfs(int v, int p, int s1, int s2) {
    ans[v] = s1 - (sz(gr[v]) - 1)*s2;
    dbg(v, ans[v], s1, s2);
    trav(u, gr[v]) {
        if (u == p) continue;
        dfs(u, v, s2, ans[v] + (sz(gr[v]) - 1)*s2);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        F0R(i, n) gr[i].clear();
        F0R(i, n-1) {
            int a, b; cin >> a >> b; a--; b--;
            gr[a].pb(b);
            gr[b].pb(a);
        }
        memset(ans, 0, sizeof ans);
        F0R(i, n) {
            int cnt = 0;
            trav(v, gr[i]) {
                if (sz(gr[v]) == 1) cnt++;
            }
            if (sz(gr[i]) == 1 || cnt < sz(gr[i])-1) continue;
            ans[i] = -sz(gr[i]);
            int w = -1;
            trav(v, gr[i]) {
                if (sz(gr[v]) == 1) ans[v] = 1;
                else w = v;
            }
            dbg(i, w);
            if (w != -1) dfs(w, i, 1, -1);
            break;
        }
        F0R(i, n) cout << ans[i] << " "; cout << nl;
    }

    return 0;
}
