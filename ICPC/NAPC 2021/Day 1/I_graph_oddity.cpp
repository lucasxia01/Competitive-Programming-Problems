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

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    int deg[n+1]; memset(deg, 0, sizeof(deg));
    vi gr[n+1];
    F0R(i, m) {
        int a, b; cin >> a >> b;
        deg[a]++;
        deg[b]++;
        gr[a].pb(b);
        gr[b].pb(a);
    }
    vi order;
    priority_queue<pi, vector<pi>, greater<pi> > p;
    F0R(i, n) p.push(mp(deg[i+1], i+1));
    int k = 0;
    FOR(i, 1, n) ckmax(k, deg[i]);
    if (k%2 == 0) k++;
    while (!p.empty()) {
        pi x = p.top(); p.pop();
        int v = x.s;
        if (x.f != deg[v]) continue;
        order.pb(v);
        deg[v] = 0;
        trav(u, gr[v]) {
            if (deg[u] == 0) continue;
            deg[u]--;
            p.push(mp(deg[u], u));
        }
    }
    reverse(all(order));
    int c[n+1]; memset(c, 0, sizeof c);
    trav(v, order) {
        // cout << v << nl;
        bool used[k+1]; memset(used, 0, sizeof(used));
        trav(u, gr[v]) used[c[u]] = 1;
        int ans = 0;
        FOR(i, 1, k) {
            if (!used[i]) {
                ans = i;
                break;
            }
        }
        c[v] = ans;
    }
    cout << k << nl;
    FOR(i, 1, n) cout << c[i] << nl;
    return 0;
}
