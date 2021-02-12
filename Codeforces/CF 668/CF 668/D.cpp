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

void dbg_out () {cerr << endl;}
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) {
    cerr << H << " "; dbg_out(T...);
}

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int n;
int getSis(int x) {
    return ((x-1)+n)%(2*n)+1;
}
int other[MX];
int vis[MX];
ll sum = 0;
void dfs(int x) {
    if (vis[x]) return;
    vis[x] = 1;
    sum += x;
    vis[other[x]] = 2;
    dfs(getSis(other[x]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    if (!(n&1)) {
        cout << "First" << nl;
        cout.flush();
        F0R(i, 2*n) cout << i%n+1 << " "; cout << nl;
        cout.flush();
    } else {
        cout << "Second" << nl;
        cout.flush();
        int a[2*n]; F0R(i, 2*n) cin >> a[i];
        vi b[n];
        F0R(i, 2*n) b[a[i]-1].pb(i+1);
        
        F0R(i, n) { other[b[i][0]] = b[i][1]; other[b[i][1]] = b[i][0]; }
        // we want each of 0, ..., n-1 mod n
        F0R(i, n) dfs(i+1);
        FOR(i, 1, 2*n) if (vis[i] == (sum&1)+1) cout << i << " "; cout << nl;
        cout.flush();
    }
    return 0;
}
