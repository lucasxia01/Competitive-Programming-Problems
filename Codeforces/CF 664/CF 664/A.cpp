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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, d, m;
    cin >> n >> d >> m;
    vl hi, lo;
    int a[n];
    ll loSum = 0;
    F0R(i, n) {
        cin >> a[i];
        if (a[i] > m) hi.pb(a[i]);
        else {
            lo.pb(a[i]);
            loSum += a[i];
        }
    }
    sort(hi.begin(), hi.end(), greater<ll>()); sort(lo.begin(), lo.end(), greater<ll>());
    int l = (sz(hi)+d)/(d+1), r = min(sz(hi), (n+d)/(d+1));
    if (l==0) {
        cout << loSum << nl;
        return 0;
    }
    int j = sz(lo)-1;
    ll hiSum = 0;
    F0R(i, l-1) hiSum += hi[i];
    ll ans = 0;
    FOR(i, l-1, r-1) {
        while (j+1 > n-(i*(d+1)+1)) {
            loSum -= lo[j];
            j--;
        }
        hiSum += hi[i];
        ckmax(ans, hiSum+loSum);
    }
    cout << ans << nl;
    return 0;
}
