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
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int msb(int x) {
    return 31-__builtin_clz(x);
}

int solve(vi v) {
    int ans = MOD;
    if (sz(v) == 1) return 0;
    vi groups[32];
    trav(a, v) {
        if (a == 0) groups[0].pb(a);
        else groups[msb(a)+1].pb(a^(1<<(msb(a))));
    }
    int cnt = 0;
    int maxfirsttwo = 0;
    int sum = 0;
    F0R(i, 32) if (sz(groups[i])) {
        if (cnt < 2) ckmax(maxfirsttwo, sz(groups[i]));
        cnt++;
        sum += sz(groups[i]);
    }
    int remGroups = cnt, remSize = sum;
    sum = 0;
    F0R(i, 32) {
        if (sz(groups[i])) {
            remGroups--;
            remSize-=sz(groups[i]);
            ckmin(ans, max(sum-1,0)+remSize-remGroups+(solve(groups[i])));
            sum += sz(groups[i]);
        }
    }
    if (maxfirsttwo >= 2) cnt++;
    ckmin(ans, sz(v)-cnt);
//    trav(a, v) cout << a << " "; cout << ans << nl;
    return ans;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vi a(n); F0R(i, n) cin >> a[i];
    sort(all(a));
    cout << solve(a) << nl;
    return 0;
}
