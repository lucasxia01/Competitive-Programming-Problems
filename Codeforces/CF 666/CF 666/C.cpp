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
const ll INF = (1LL<<55) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}
void dbg_out () {cerr << endl;}
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) {
    cerr << H << " "; dbg_out(T...);
}

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    ll r1, r2, r3; cin >> r1 >> r2 >> r3;
    ll d; cin >> d;
    ll a[n], b[n], c[n];
    ll sum = 0;
    F0R(i, n) {
        cin >> a[i];
        b[i] = min(2*d+min((a[i]+1)*r1, r2)+r1, r1*a[i]+r3);
        if (i != n-1) c[i] = min(r1*a[i]+r3, min((a[i]+1)*r1, r2)+r1);
        else c[i] = b[i];
//        cout << b[i] << " " << c[i] << nl;
        sum += c[i];
    }
    ll ans = INF;
    ll leftSum[n+1]; F0R(i, n+1) leftSum[i] = INF; leftSum[0] = 0;
    F0R(i, n) {
        ll cur = d*(n-1 + n-1-i);
        cur += leftSum[i] + sum;
//        cout << i << " " << leftSum[i] << " " << sum << " " << cur << nl;
        ckmin(ans, cur);
        sum -= c[i];
        leftSum[i+1] = leftSum[i] + b[i];
        if (i > 0) {
            ckmin(leftSum[i+1], leftSum[i-1]+min((a[i]+1)*r1, r2)+r1+min((a[i-1]+1)*r1, r2)+r1+2*d);
        }
        if (i == n-1) ckmin(ans, d*(n-1)+leftSum[i+1] + sum);
    }
    cout << ans << nl;
    return 0;
}
