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

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 100000+5;
int m[MX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int a, b, c; cin >> a >> b >> c;
    int ans = 0;
    F0R(i, a) {
        int x; cin >> x;
        m[x]++;
    }
    F0R(i, b) {
        int x; cin >> x;
        m[x]+=2;
    }
    F0R(i, c) {
        int x; cin >> x;
        m[x]+=4;
    }
    int f[8] = {};
    F0R(i, MX) {
        f[m[i]]++;
    }
    ans = f[7];
    int x = min(f[1], f[6]);
    ans += x; f[1] -= x; f[6] -= x;
    x = min(f[2], f[5]);
    ans += x; f[2] -= x; f[5] -= x;
    x = min(f[4], f[3]);
    ans += x; f[4] -= x; f[3] -= x;
    ans += max(f[1], max(f[2], f[4]));
    ans += f[6] + f[5] + f[3];
    cout << ans << nl;
    return 0;
}
