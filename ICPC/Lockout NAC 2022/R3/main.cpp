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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int a[60] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 
    31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31
    int n; cin >> n;
    int b[n]; F0R(i, n) cin >> b[i];
    int ans = 0;
    F0R(j, 60) {
        bool ok = 1;
        F0R(i, n) {
                // if (j == 6) cout << a[i+j] << " " << b[i] << nl;
                if (i+j >= 60) {
                    ok = 0;
                    break;
                }
                if (b[i] != a[i+j]) ok = 0;
            }
        if (ok) ans = 1;
    }
    cout << (ans?"Yes":"No") << nl;
    return 0;
}
