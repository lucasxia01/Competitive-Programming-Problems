#include <vector>
#include <stack>
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <functional>
#include <set>
#include <cstring>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>
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
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define trav(a, x) for (auto& a : x)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 998244353;
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()
ll ee(ll a, ll b, ll* x, ll* y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    ll w, z;
    ll ret = ee(b%a, a, &w, &z);
    *x = z - (b/a)*w;
    *y = w;
    return ret;
}

ll inv(ll k) {
    ll x, y;
    ee(k, MOD, &x, &y);
    return (x + MOD)%MOD;
}

ll fact(ll n) {
    ll ans = 1;
    FOR(i, 1, n+1) {
        ans = (ans * i) % MOD;
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    pl a[n], b[n];
    F0R(i, n) cin >> a[i].f >> a[i].s;
    F0R(i, n) {
        b[i].f = a[i].s;
        b[i].s = a[i].f;
    }
    sort(a, a+n);
    map<ll, ll> count;
    ll ans1 = 1, ans2 = 1, ans3 = 1;
    int c = 0;
    F0R(i, n) {
        c++;
        if (count.find(a[i].s) == count.end()) {
            count.insert(mp(a[i].s, 1));
        } else {
            count[a[i].s]++;
        }
        if (i == n-1 || a[i].f != a[i+1].f) {
            ll x = fact(c);
            ans1 = (ans1 * x) % MOD;
            c = 0;
            trav(au, count) {
                ans3 = (ans3 * fact(au.s)) % MOD;
            }
            count.clear();
        }
    }
    
    
    
    sort(b, b+n);
    ll ans4 = 1;
    F0R(i, n) {
        c++;
        if (count.find(b[i].s) == count.end()) {
            count.insert(mp(b[i].s, 1));
        } else {
            count[b[i].s]++;
        }
        if (i == n-1 || b[i].f != b[i+1].f) {
            ll x = fact(c);
            ans2 = (ans2 * x) % MOD;
            c = 0;
            trav(au, count) {
                ans4 = (ans4 * fact(au.s)) % MOD;
            }
            count.clear();
        }
    }
    
    
    bool good = true;
    F0R(i, n-1) {
        if (a[i+1].s < a[i].s) good = false;
    }
//    cout << ans1 << endl;
//    cout << ans2 << endl;
//    cout << ans3 << " " << ans4 << endl;
    assert(ans3 == ans4);
    if (!good) ans3 = 0;
    cout << ((fact(n) - (ans1+ans2-ans3)%MOD)%MOD+MOD)%MOD << endl;
    return 0;
}
