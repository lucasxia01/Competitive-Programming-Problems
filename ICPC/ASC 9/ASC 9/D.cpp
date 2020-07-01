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

typedef __int128 ll;
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

std::ostream&
operator<<( std::ostream& dest, __int128_t value )
{
    std::ostream::sentry s( dest );
    if ( s ) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do
        {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );
        if ( value < 0 ) {
            -- d;
            *d = '-';
        }
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}

const int MX = 105;

vi gr[MX], revgr[MX];
int vis[MX];
vi cgr[MX]; // compressed SCC graph
int csz[MX]; // size of each component
vi order;
void dfs1(int v) {
    vis[v] = 1;
    trav(u, gr[v]) {
        if (vis[u]) continue;
        dfs1(u);
    }
    order.pb(v);
}
int mark = 0, comp = 0;
void dfs2(int v) {
    vis[v] = mark;
    comp++;
    trav(u, revgr[v]) {
        if (vis[u]) continue;
        dfs2(u);
    }
}

bool in[MX];
bool out[MX];

ll comb[MX][MX];
ll calc(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    if (comb[n][k]) return comb[n][k];
    return (comb[n][k]=calc(n-1, k)+calc(n-1, k-1));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("police.in", "r", stdin);
//    freopen("police.out", "w", stdout);
    int n, m, k; cin >> n >> m >> k;
    int u, v;
    F0R(i, m) {
        cin >> u >> v;
        gr[u].pb(v);
        revgr[v].pb(u);
    }
    FOR(i, 1, n) if (!vis[i]) dfs1(i);
    reverse(order.begin(), order.end());
    memset(vis, 0, sizeof vis);
    vi policeComps;
    int rest = 0;
    trav(a, order) {
        if (!vis[a]) {
            ++mark;
            comp = 0;
            dfs2(a);
            csz[mark] = comp;
        }
    }
    FOR(i, 1, n) trav(v, gr[i]) if (vis[v] != vis[i]) in[vis[v]] = 1, out[vis[i]] = 1;
    FOR(i, 1, mark) if (!in[i] || !out[i]) policeComps.pb(csz[i]); else rest += csz[i];
    int SZ = sz(policeComps);
    ll dp[SZ+1][k+1]; F0R(i, SZ+1) F0R(j, k+1) dp[i][j] = 0;
    dp[0][0] = 1;
    F0R(i, SZ) {
        F0R(j, k+1) {
            FOR(l, 1, policeComps[i]) {
                if (j+l > k) break;
                dp[i+1][j+l] += (ll)calc(policeComps[i], l)*dp[i][j];
            }
        }
    }
    ll ans = 0;
    F0R(j, k+1) {
//        cout << dp[SZ][j] << " " << calc(rest, k-j) << nl;
        ans += (ll)calc(rest, k-j)*dp[SZ][j];
    }
    cout << ans << nl;
    return 0;
}
