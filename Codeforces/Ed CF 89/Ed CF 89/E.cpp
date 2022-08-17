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
const ll MOD = 998244353;
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    int a[n]; F0R(i, n) cin >> a[i];
    int b[m]; F0R(i, m) cin >> b[i];
    int last[m]; F0R(i, m) last[i] = -1;
    int first[m]; F0R(i, m) first[i] = -1;
    int M = -1;
    F0Rd(i, n) {
        if (M == -1 && a[i] < b[0]) M = i;
        ll idx = upper_bound(b, b+m, a[i])-b-1;
        if (idx == -1) continue;
        if (b[idx] == a[i] && last[idx] == -1) last[idx] = i;
        if (first[idx] == -1) first[idx] = i;
    }
    ll ans = 1;
    F0R(i, m) if (last[i] == -1 || first[i] == -1) ans = 0;
    if (M != -1) ans = 0;
    FOR(i, 1, m-1) {
        if (last[i]-first[i-1] <= 0) ans = 0;
        ans = (ans * (last[i]-first[i-1]))%MOD;
    }
    cout << ans << nl;
    return 0;
}
