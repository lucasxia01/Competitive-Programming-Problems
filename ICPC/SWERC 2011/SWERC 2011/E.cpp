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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MX = 100;

ll cm[MX][MX];
ll comb(ll n, ll r) {
    if (r == 0 || n == r) return 1;
    if (n < r || n < 0 || r < 0) return 0LL;
    if (cm[n][r]) return cm[n][r];
    return comb(n-1, r) + comb(n-1, r-1);
}

ld win(ld p, int n) {
    ld pn = powl(p, n);
    ld ret = 0;
    F0R(i, n-1) ret += pn*comb(n-1+i, i)*powl(1-p, i);
    ret += comb(2*n-2, n-1)*powl(p, n-1)*powl(1-p, n-1)*(p*p)/(1 - 2*p*(1-p));
    return ret;
}

ld win_set(ld p, ld point) {
    int n = 6;
    ld pn = powl(p, n);
    ld ret = 0;
    F0R(i, n-1) ret += pn*comb(n-1+i, i)*powl(1-p, i);
    ret += comb(2*n-2, n-1)*powl(p, n-1)*powl(1-p, n-1)*2*p*(1-p)*win(point, 7);
    ret += comb(2*n-2, n-1)*powl(p, n-1)*powl(1-p, n-1)*p*p;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for (ld n; cin >> n && n != -1;) {
        ld game = win(n, 4);
        ld set = win_set(game, n);
        ld match = set*set + 2*set*(1-set)*set;
        cout << setprecision(10);
        cout << fixed << game << " " << set << " " << match << nl;
    }
    return 0;
}
