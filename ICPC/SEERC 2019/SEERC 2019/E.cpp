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
const ll INF = 1e15;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll n, k; cin >> n >> k;
    ll ac, pc, am, pm; cin >> ac >> pc >> am >> pm;
    ll t, d; cin >> t >> d;
    ll a[n]; F0R(i, n) cin >> a[i];
    sort(a, a+n, greater<int>());
    ll extra = 0;
    ll numTrans = 0;
    bool ok = 1;
    F0R(i, n) { // computing extra years and years needed for all motorcycles
        extra += min(max(a[i]-am, 0LL), d);
        numTrans += max(am-a[i], 0LL);
        if (am-a[i] > d) ok = 0;
    }
    ok = (ok&&extra >= numTrans);
    ll num_cars = 0, num_mot = n, ans = (ok ? numTrans*t+pm*n : INF);
    while (num_cars*k < n) {
        if (am-a[num_cars] > d) break;
        extra -= min(max(a[num_cars]-am, 0LL), d);
        numTrans -= max(am-a[num_cars], 0LL);
        extra += min(max(a[num_cars]-ac, 0LL), d);
        numTrans += max(ac-a[num_cars], 0LL);
        for (ll i = num_cars+num_mot-1; i >= num_cars+1+max(n-(num_cars+1)*k, 0LL); i--) {
            extra -= min(max(a[i]-am, 0LL), d);
            numTrans -= max(am-a[i], 0LL);
            extra += min(a[i]-1, d);
            numTrans += 0;
        }
        num_mot = max(n-(num_cars+1)*k, 0LL);
        num_cars++;
        if (numTrans > extra) continue;
        ckmin(ans, num_cars*pc+num_mot*pm+numTrans*t);
    }
    cout << (ans == INF ? -1 : ans) << nl;
    return 0;
}
