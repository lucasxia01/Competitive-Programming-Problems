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

const int MX = 1<<20;

ll binpow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a)%MOD;
        a = (a * a)%MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, r, c, k; cin >> n >> r >> c >> k;
    ll fr[r][r], fc[c][c], gr[r][r], gc[c][c];
    ll sumR[r], sumC[c]; F0R(i, r) sumR[i] = 0; F0R(i, c) sumC[i] = 0;
    int N = max(r, c)+1;
    ll powers[N]; F0R(i, N) powers[i] = binpow(i, n);
    F0R(i, r) F0R(j, i+1) fr[j][i] = (powers[j+1]*powers[r-i])%MOD;
    F0R(i, c) F0R(j, i+1) fc[j][i] = (powers[j+1]*powers[c-i])%MOD;
    F0R(i, r) F0R(j, i+1) {
        gr[j][i] = fr[j][i];
        if (j > 0) gr[j][i] -= fr[j-1][i];
        if (i < r-1) gr[j][i] -= fr[j][i+1];
        if (j > 0 && i < r-1) gr[j][i] += fr[j-1][i+1];
//        dbg(j, i, fr[j][i], gr[j][i]);
        gr[j][i] %= MOD;
        sumR[i-j] += gr[j][i];
    }
    F0R(i, c) F0R(j, i+1) {
        gc[j][i] = fc[j][i];
        if (j > 0) gc[j][i] -= fc[j-1][i];
        if (i < c-1) gc[j][i] -= fc[j][i+1];
        if (j > 0 && i < c-1) gc[j][i] += fc[j-1][i+1];
//        dbg(j, i, fc[j][i], gc[j][i]);
        gc[j][i] %= MOD;
        sumC[i-j] += gc[j][i];
    }
    ll ans = 0;
    F0R(i, r) sumR[i] = (sumR[i]%MOD+MOD)%MOD; F0R(i, c) sumC[i] = (sumC[i]%MOD+MOD)%MOD;
    F0R(i, r) F0Rd(j, c) {
        if ((i+1)*(j+1) >= k) ans += (sumR[i]*sumC[j])%MOD;
        else break;
    }
    cout << ans%MOD << nl;
    return 0;
}
