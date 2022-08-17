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
const int INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e5+5;

int fenw[MX];
void upd(int i, int v) {
    while (i < MX) {
        fenw[i] += v;
        i += i&-i;
    }
}

int query(int i) {
    int ret = 0;
    while (i) {
        ret += fenw[i];
        i -= i&-i;
    }
    return ret;
}

int n;
int r1[MX], r2[MX];
ll solve() {
    int a[n+1], b[n+1];
    int m[n+1];
    FOR(i, 1, n) {
        a[i] = r1[i];
        m[a[i]] = i; // mapping it to 1-n
        a[i] = i;
    }
    int pos[n+1];
    FOR(i, 1, n) {
        b[i] = r2[i];
        b[i] = m[b[i]];
        pos[b[i]] = i;
    }
    ll numInv = 0;
    FORd(i, 1, n) {
        // cout << i << " " << pos[i] << " " << query(pos[i]) << nl;
        numInv += 1LL*query(pos[i]);
        upd(pos[i], 1);
    }
    ll ret = numInv, cur = numInv;
    FORd(i, 2, n) {
        cur -= 1LL*(n-b[i]) - (b[i]-1);
        // cout << b[i] << " " << cur << nl;
        ckmin(ret, cur);
    }
    return ret;
    
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    freopen("mincross.in", "r", stdin);
    freopen("mincross.out", "w", stdout);
    cin >> n;
    F0R(i, n) cin >> r1[i+1];
    F0R(i, n) cin >> r2[i+1];
    ll ans1 = solve();
    memset(fenw, 0, 4*MX);
    swap(r1, r2);
    ll ans2 = solve();
    cout << min(ans1, ans2) << nl;
    return 0;
}
