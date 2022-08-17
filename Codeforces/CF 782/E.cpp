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

int p[30][MX], sz[30][MX];
bool escapable[30][MX];

int find(int i, int v) {
    return (v == p[i][v] ? v : p[i][v] = find(i, p[i][v]));
}

void merge(int i, int a, int b) {
    a = find(i, a); b = find(i, b);
    if (a == b) return;
    if (sz[i][a] < sz[i][b]) swap(a, b);
    sz[i][a] += sz[i][b];
    p[i][b] = a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    F0R(j, 30) FOR(i, 1, n) {
        p[j][i] = i;
        sz[j][i] = 1;
    }
    vector<pair<pi, int> > es;
    F0R(i, m) {
        int a, b, w;
        cin >> a >> b >> w;
        F0R(j, 30) {
            if (w&(1<<j)) merge(j, a, b);
        }
        es.pb({{a, b}, w});
    }
    // figure out which components u can escape from
    trav(e, es) {
        int a = e.f.f, b = e.f.s, w = e.s;
        // if they are in different 0 components
        if ((w&1) == 0) {
            // now for all the other dudes, we want to say that they can escape
            FOR(i, 1, 29) {
                escapable[i][find(i, a)] = escapable[i][find(i, b)] = 1;
                
            }
        }
    }

    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        // first check that same component in any bit
        bool ok = 0;
        F0R(i, 30) {
            if (find(i, u) == find(i, v)) {
                ok = 1;
            }
        }
        if (ok) {
            cout << 0 << nl;
            continue;
        }
        // now check if we can escape from u
        ok = 0;
        F0R(i, 30) {
            if (escapable[i][find(i, u)]) ok = 1;
        }
        cout << (ok?1:2) << nl;
    }
    return 0;
}
