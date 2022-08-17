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

const int MX = 5e5+5;

int n;

vector<pair<int, pi> > gr[MX];
int p[2*MX], sz[2*MX];
int last_seen[MX];

int find_set(int v) {
    if (v == p[v])
        return v;
    return p[v] = find_set(p[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b])
            swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
    }
}

// merge all the stuff in components
void dfs(int v, int p) {
    trav(u, gr[v]) {
        if (u.f == p) continue;
        int x = u.s.f, i = u.s.s;
        if (last_seen[x] != -1) {
            // merge stuff in the dsu
            union_sets(last_seen[x], (i^1));
        }
        last_seen[x] = i;
        dfs(u.f, v);
        last_seen[x] = i^1;
    }
}

int subtree_sz[2*MX];
int count(int v, int p) {
    int ret = 1;
    trav(u, gr[v]) {
        if (u.f == p) continue;
        int x = u.s.f, i = u.s.s;
        int ans = count(u.f, v);
        ret += ans;
        subtree_sz[i^1] = ans+1;  
        subtree_sz[i] = n - (subtree_sz[i^1]-2);
    }
    return ret;
}

vi comps[2*MX];
ll cnt[2*MX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    F0R(i, n-1) {
        int a, b, c; cin >> a >> b >> c;
        gr[a].pb({b, {c, 2*i}});
        gr[b].pb({a, {c, 2*i+1}});
        // dbg(a, b, 2*i);
        // dbg(b, a, 2*i+1);
    }
    F0R(i, 2*n) {
        p[i] = i;
        sz[i] = 1;
    }
    F0R(i, n+1) last_seen[i] = -1;
    // merge comps
    dfs(1, 0);
    // find subtree sizes
    count(1, 0);
    // F0R(i, 2*(n-1)) {
    //     dbg("SIZE", i, subtree_sz[i]);
    // }
    // now iterate through components 
    F0R(i, 2*n) {
        comps[find_set(i)].pb(i);
    }

    F0R(i, 2*n) {
        if (!sz(comps[i])) continue;
        int sum = 0;
        trav(j, comps[i]) sum += subtree_sz[j]-1;
        trav(j, comps[i]) cnt[j] = n-sum;
        // dbg(i, n-sum);
        // trav(j, comps[i]) cerr << j <<' '; cerr << nl;
    }
    ll ans = 0;
    F0R(i, n-1) {
        // dbg(2*i, 2*i+1, cnt[2*i], cnt[2*i+1]);
        ans += (ll)cnt[2*i]*cnt[2*i+1];
    }
    cout << ans << nl;
    return 0;
}
