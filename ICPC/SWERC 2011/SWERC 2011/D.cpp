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

struct city {
    ll n, b, i;
    bool operator<(const city& o) const {
        return (n*(o.b-1) >= o.n*(b-1));
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for (int n, b; cin >> n >> b;) {
        if (n == -1) break;
        ll sum = 0;
        ll a[n];
        F0R(i, n) {
            cin >> a[i];
            sum += a[i];
        }
        ll c = sum/b;
        vector<city> v;
        int used = 0;
        F0R(i, n) {
            v.pb({a[i], (a[i]+c-1)/c, i});
            used += (a[i]+c-1)/c;
        }
        assert(used >= b);
        priority_queue<city> S;
        ll ans = 0;
        F0R(i, n) {
            if (v[i].b != 1) S.push(v[i]);
            ckmax(ans, (v[i].n+v[i].b-1)/v[i].b);
        }
        F0R(i, used-b) {
            auto [nn, bb, ii] = S.top();
            // cout << nn << " " << bb << nl;
            S.pop();
            if (bb-1 != 1) {
                S.push({nn, bb-1, ii});
                ckmax(ans, (nn+bb-2)/(bb-1));
            } else ckmax(ans, nn);
        }
        cout << ans << nl;
    }
    
    return 0;
}
