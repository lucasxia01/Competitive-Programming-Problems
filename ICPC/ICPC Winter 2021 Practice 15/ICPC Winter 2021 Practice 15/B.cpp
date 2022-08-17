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

const int MX = 1<<16;
ld a[100][MX];
ld p1[1<<8], p2[1<<8];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int k, v; cin >> k >> v;
    int n = (1<<k);
    F0R(j, v) F0R(i, n) a[j][i] = 0;
    a[0][0] = 1;
    F0R(i, v-1) {
        ld p; int b; cin >> p >> b;
        F0R(j, n) {
            a[i+1][j] += a[i][j]*((ld)1-p);
            a[i+1][(j+b)%n] += a[i][j]*p;
        }
    }
//    F0R(i, n) cout << a[v-1][i] << " "; cout << nl;
    int K = min(256, 1<<k);
    F0R(i, n) {
        p1[i%K] += a[v-1][i];
        p2[i>>8] += a[v-1][i];
    }
    
//    F0R(i, 1<<8) cout << p1[i] << " "; cout << nl;
//    F0R(i, 1<<8) cout << p2[i] << " "; cout << nl;
    
    ld best = 0, ans = -1;
    F0R(i, n) {
        ld curAns = 0;
        F0R(j, K) {
            curAns += (p1[j]+p2[j])*__builtin_popcount(j);
        }
        if (ckmax(best, curAns)) ans = i;
        ld temp = p1[K-1];
        F0Rd(j, K-1) p1[j+1] = p1[j];
        p1[0] = temp;
        if (k > 8) {
            int K2 = min(256, 1<<(k-8));
            F0R(j, K2) {
                p2[(j+1)%K2] += a[v-1][(j*256 + 255-i+n)%n];
                p2[j] -= a[v-1][(j*256 + 255-i+n)%n];
            }
        }
//        dbg(i, curAns);
    }
    cout << ans << nl;
    return 0;
}
