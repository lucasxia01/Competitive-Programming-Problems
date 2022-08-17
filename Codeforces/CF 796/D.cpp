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

#define int ll

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

const int MX = 4e6+6;
int nxt[2*MX], pref[2*MX];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int a[n]; F0R(i, n) cin >> a[i];
    int p = n-1;
    pref[0] = 0;
    nxt[2*MX-1] = INF;
    FORd(i, 0, 2*MX-2) {
        if (p == -1 || i != a[p]) { nxt[i] = nxt[i+1]; continue; }
        while (p >= 0 && i == a[p]) nxt[i] = a[p--];
    }
    p = 0;
    FOR(i, 1, 2*MX-1) {
        pref[i] = pref[i-1];
        while (p < n && i == a[p]) { pref[i]++; p++; }
    }
    // try everything from 1 to 4*10^6
    FOR(i, 1, 2*a[n-1]+2) {
        if (a[0]-i > i*i) continue;
        int offset = 0;
        int len = i;
        int l = a[0];
        while (l-i < a[n-1]) {
            int val = a[0];
            if (l-i >= 0) val = nxt[l-i];
            ckmin(offset, val-l);
            l += 2*len+1;
            len++;
        }
        ckmin(offset, i*i-a[0]);
        int cnt = 0;
        len = i;
        l = a[0]+offset;
        while (l <= a[n-1]) {
            int val = 0;
            if (l-1 >= 0) val = pref[l-1];
            cnt += pref[l+len]-val;
            l += 2*len+1;
            len++;
        }
        if (cnt == n) {
            cout << i*i-offset-a[0] << nl;
            return 0;
        }
    }
    assert(0);
    return 0;
}
