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

const int MX = 100<<20, MXN = 100;
int a[MXN];
int n;
vpi ops;

const int N = 7;
int dp[MX], vis[MX];
int targetState;

void check0(int a[N], int k) {
    int state = 0;
    F0R(i, N) state = 10*state+a[i];
    vis[state] = 1;
    if (k == 0) return;
    F0R(i, N-1) FOR(j, i+1, N-1) {
        if (a[j] < a[j-1]) break;
        reverse(a+i, a+j+1);
        check0(a, k-1);
        reverse(a+i, a+j+1);
    }
    F0R(i, N-1) FOR(j, i+1, N-1) {
        if (a[j] > a[j-1]) break;
        reverse(a+i, a+j+1);
        check0(a, k-1);
        reverse(a+i, a+j+1);
    }
}

bool check(int a[N], int k) {
    int state = 0;
    F0R(i, N) state = 10*state+a[i];
    if (state == targetState) return 1;
    if (dp[state] > k) return 0;
    dp[state] = k;
    if (k == 0) return 0;
    F0R(i, N-1) FOR(j, i+1, N-1) {
        if (a[j] < a[j-1]) break;
        reverse(a+i, a+j+1);
        if (check(a, k-1)) {
//            dbg(i+1, j+1);
            ops.pb({i+1, j+1});
            return 1;
        }
        reverse(a+i, a+j+1);
    }
    F0R(i, N-1) FOR(j, i+1, N-1) {
        if (a[j] > a[j-1]) break;
        reverse(a+i, a+j+1);
        if (check(a, k-1)) {
//            sdbg(i+1, j+1);
            ops.pb({i+1, j+1});
            return 1;
        }
        reverse(a+i, a+j+1);
    }
    return 0;
}

void sort_first_7_in_6() {
    int test[N] = {1, 2, 3, 4, 5, 6, 7};
    int t[N]; F0R(i, N) t[i] = a[i]; // coord compress to 1 to 7
    sort(t, t+N);
    map<int, int> m; F0R(i, N) m[t[i]] = i+1;
    F0R(i, N) targetState = 10*targetState+m[a[i]];
//    cout << targetState << nl;
    if (!check(test, 6)) {
        assert(0);
    }
//    F0R(i, N) {
//        dbg(test[i]);
//        test[i] = i+1;
//    }
//    check0(test, 6);
//    do {
//        int state = 0;
//        F0R(i, N) state = 10*state+test[i];
//        if (!vis[state]) cout << state << nl;
//    } while (next_permutation(test, test+N));
    sort(a, a+N);
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    F0R(i, n) cin >> a[i];
    int cur = 1;
    bool rev = 0;
    if (n >= 7) {
        F0R(i, 7) {
            if (a[i] == n) rev = 1;
        }
        if (rev) reverse(a, a+n);
        sort_first_7_in_6();
        cur = 7;
    }
    
    while (cur < n) { // insertion pancake thing
        int i = cur-1;
        while (a[i] > a[cur]) i--;
        if (i+2 < cur) ops.pb({i+1+1, cur});
        if (i+2 < cur+1) ops.pb({i+1+1, cur+1});
        sort(a, a+cur+1);
        cur++;
    }
    
    if (rev) {
        ops.pb({1, n});
    }
    cout << sz(ops) << nl;
    trav(o, ops) {
        if (rev) o = {n+1-o.s, n+1-o.f};
    }
    trav(o, ops) cout << o.f << " " << o.s << nl;
    
    
    return 0;
}
