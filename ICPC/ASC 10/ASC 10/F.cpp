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

const int MX = 1<<20;

int n;
ld r, h;
ld calc(ld diff) {
    while (diff > 2*PI) diff -= 2*PI;
    if (diff >= PI) diff = 2*PI-diff;
    assert(diff >= 0 && diff <= PI);
    return sqrtl(h/2*h/2+(r*diff*r*diff));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen("magic.in", "r", stdin);
//    freopen("magic.out", "w", stdout);
    cin >> n >> r >> h;
    pair<ld, int> l[3][n]; F0R(i, 3) F0R(j, n) {
        cin >> l[i][j].f;
        if (l[i][j].f < 0) l[i][j].f += 2*PI;
    }
    F0R(i, 3) F0R(j, n) l[i][j].s = j;
    F0R(i, 3) sort(l[i], l[i]+n);
    ld minAns1 = INF; int minIdx1 = -1;
    F0R(j, n) {
        ld total = 0;
        F0R(i, n) total += calc(min(abs(l[0][i].f-l[1][(i+j)%n].f), 4*PI-abs(l[0][i].f-l[1][(i+j)%n].f)));
        if (ckmin(minAns1, total)) minIdx1 = j;
    }
    ld minAns2 = INF; int minIdx2 = -1;
    F0R(j, n) {
        ld total = 0;
        F0R(i, n) total += calc(min(abs(l[1][i].f-l[2][(i+j)%n].f), 4*PI-abs(l[1][i].f-l[2][(i+j)%n].f)));
        if (ckmin(minAns2, total)) minIdx2 = j;
    }
    cout.precision(8);
    cout << fixed << minAns1 + minAns2 << nl;
    F0R(i, n) {
        cout << l[0][i].s+1 << " " << l[1][(i+minIdx1)%n].s+1 << " " << l[2][(i+minIdx1+minIdx2)%n].s+1 << nl;
    }
    return 0;
}
