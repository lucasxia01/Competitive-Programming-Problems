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

const ll MX = 1LL<<31;

ll bs(ll x) {
    if (x < 0) return 0;
    ll lo = 0, hi = MX, mid = MX/2;
    while (lo < hi) {
        if (mid*(mid+1)/2 >= x) hi = mid;
        else lo = mid+1;
        mid = (lo+hi)/2;
    }
    assert(mid*(mid+1)/2 >= x && mid*(mid-1)/2 < x);
    return mid;
}

ll arithsum(ll lo, ll hi) {
    return (hi+lo)/2 * ((hi-lo)/2+1);
}
void solve() {
    ll l, r;
    cin >> l >> r;
    ll p = 0;
    if (l >= r) {
        ll mid = bs(l-r+1);
        mid--;
        ll temp = mid*(mid+1)/2;
        assert(temp <= l-r);
        p = mid;
        l -= temp;
    } else {
        ll mid = bs(r-l);
        ll temp = mid*(mid+1)/2;
        if (temp > r) {
            cout << mid-1 << " " << l << " " << r-mid*(mid-1)/2 << nl;
            return;
        }
        p = mid;
        r -= temp;
    }
    assert(l >= r);
    // cout << p << " " << l << " " << r << nl;
    ll t = l+r;
    ll mid = bs(t);
    assert(mid*(mid+1)/2 > t || (mid+1)*(mid+2)/2 > t);
    ll lo = p, hi = mid+p, m = (lo+hi)/2;
    ll s1 = 0, s2 = 0;
    while (lo < hi) {
        if ((m-p)%2) {
            s1 = arithsum(p+1, m);
            s2 = arithsum(p+2, m-1);
        } else {
            s1 = arithsum(p+1, m-1);
            s2 = arithsum(p+2, m);
        }
        if (s1 > l || s2 > r) hi = m;
        else lo = m+1;
        m = (lo+hi)/2;
    }
    if ((m-p)%2) {
        s1 = arithsum(p+1, m);
        s2 = arithsum(p+2, m-1);
    } else {
        s1 = arithsum(p+1, m-1);
        s2 = arithsum(p+2, m);
    }
    if (s1 > l || s2 > r) m--;
    if ((m-p)%2) {
        s1 = arithsum(p+1, m);
        s2 = arithsum(p+2, m-1);
    } else {
        s1 = arithsum(p+1, m-1);
        s2 = arithsum(p+2, m);
    }
    cout << m << " " << l-s1 << " " << r-s2 << nl;
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    F0R(i, t) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    
    return 0;
}
