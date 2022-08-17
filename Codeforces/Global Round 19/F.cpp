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
const ll INF = 1e16;
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

const int MX = 2e5+5;

vi gr[MX];
ll h[MX];
ll ans = 0;
ll t[2*MX];
int n;

void modify(int p, ll value) {  // set value at position p
  for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = max(t[p], t[p^1]);
}

ll query(int l, int r) {  // sum on interval [l, r)
  ll res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) ckmax(res, t[l++]);
    if (r&1) ckmax(res, t[--r]);
  }
  return res;
}

int T = -1;
void dfs(int v, int p) {
    T++;
    modify(T, h[v]);
    trav(u, gr[v]) {
        if (u == p) continue;
        dfs(u, v);
    }
}

// returns what node v needs
ll solve(int v, int p) {
    int in = ++T;
    vl c;
    ll ret = h[v];
    trav(u, gr[v]) {
        if (u == p) continue;
        ll x = solve(u, v);
        ckmax(ret, x);
        c.pb(x);
    }

    c.pb(max(query(0, in), query(T+1, n)));
    sort(all(c), greater<ll>());
    // dbg(v+1, sz(c), h[v]);
    // trav(cc, c) dbg(cc);
    if (sz(c) == 1) {
        if (c[0] < h[v]) ans += 2*h[v] - c[0];
        else ans += h[v];
    } else {
        if (c[1] >= h[v]) return ret;
        if (c[0] >= h[v]) ans += h[v] - c[1];
        else ans += 2*h[v] - c[0] - c[1];
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    F0R(i, n) cin >> h[i];
    F0R(i, n-1) {
        int u, v; cin >> u >> v;
        u--; v--;
        gr[u].pb(v);
        gr[v].pb(u);
    }
    int x = -1; // non-leaf
    F0R(i, n) if (sz(gr[i]) >= 2) x = i;
    if (x == -1) {
        cout << max(h[0], h[1])*2 << nl;
        return 0;
    }
    T = -1;
    dfs(x, -1);
    T = -1;
    solve(x, -1);
    cout << ans << nl;
    return 0;
}
