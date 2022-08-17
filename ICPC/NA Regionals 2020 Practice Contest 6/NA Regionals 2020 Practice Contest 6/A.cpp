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

const int MX = 5e5+5;
int n, k;
int a[2*MX];
int val = 0;
int loc[30];
bool check() {
//    dbg(val);
    F0R(i, 30) {
        if (val&(1<<i)) {
            int j = loc[i]+1;
            int cur = 0;
            int cnt = 0;
            while (j <= loc[i]+n) {
                cur |= a[j];
                if ((cur&val) == val) {
                    cnt++;
                    cur = 0;
                }
                j++;
            }
//            dbg(1<<i, cnt);
            if (cnt >= k) return 1;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    F0R(i, n) cin >> a[i];
    F0R(i, n) a[i+n] = a[i];
    int pref[30] = {};
    F0R(i, 30) loc[i] = -1;
    F0R(i, n) {
        F0R(j, 30) if ((a[i]&(1<<j)) && pref[j] == 0) {
            pref[j] = 1;
            loc[j] = i;
        }
    }
//    F0R(i, 30) dbg(loc[i]);
    F0Rd(i, 30) {
        if (loc[i] == -1) continue;
        val += (1<<i);
        if (!check()) val -= (1<<i);
    }
    cout << val << nl;
    return 0;
}
