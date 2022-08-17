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
#define rep(i, a, b) for(int i = a; i < (b); ++i)

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

#ifdef DBG
#define dbg(...) dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;
int p[MX];
int sz[MX];
tuple<int, int, int> w[MX];
vi num, st;
vector<vector<pi>> ed;
int Time;
vi bridges;

vpi gr[MX];
bool has_bridge[MX];

int f(int v) {
    return (v==p[v]?v:p[v]=f(p[v]));
}

void merge(int a, int b, int c) {
    a = f(a); b = f(b);
    has_bridge[a] |= c;
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    p[b] = a;
    has_bridge[a] |= (has_bridge[b] || c);
}

int dfs(int at, int par) {
    int me = num[at] = ++Time, e, y, top = me;
    for (auto pa : ed[at]) if (pa.second != par) {
        tie(y, e) = pa; 
        if (num[y]) {
        top = min(top, num[y]); if (num[y] < me)
                st.push_back(e);
        } else {
            int si = sz(st);
            int up = dfs(y, e); top = min(top, up);
            if (up == me) {
                    st.push_back(e);
                    vi temp = vi(st.begin() + si, st.end());
                    trav(t, temp) {
                        auto [a, b, c] = w[t];
                        // dbg(a, b, c);
                        merge(a, b, c);
                    }
                    st.resize(si);
            } else if (up < me) st.push_back(e);
            else { /* e is a bridge */
                bridges.pb(e);
            } 
        }
    }
return top; }

void bicomps() {
    num.assign(sz(ed), 0);
    rep(i,0,sz(ed)) if (!num[i]) dfs(i, -1);
}

bool ans;
void dfs1(int v, int p, int d, bool b) {
    b |= (has_bridge[v]);
    if (v == d) ans = b;
    trav(u, gr[v]) {
        if (u.f == p) continue;
        dfs1(u.f, v, d, (b|u.s));
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    int eid = 0; ed.resize(n+1);
    
    F0R(i, MX) {
        p[i] = i;
        sz[i] = 1;
    }

    F0R(i, m) {
        int a, b, c; cin >> a >> b >> c;
        ed[a].pb({b, eid});
        ed[b].pb({a, eid});
        w[eid++] = {a, b, c};
    }
    bicomps();
    trav(br, bridges) {
        auto [a, b, c] = w[br];
        gr[f(a)].pb({f(b), c});
        gr[f(b)].pb({f(a), c});
    }
    int x, y; cin >> x >> y;
    dfs1(f(x), -1, f(y), 0);
    cout << (ans?"YES":"NO") << nl;
}
