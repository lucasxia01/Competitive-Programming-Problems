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

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
ll MOD; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

const int MX = 1e6+5;

ll mod_pow(ll a, ll b) {
       if (b == 0) return 1LL;
       ll p = mod_pow(a, b >> 1);
       p = p * p % MOD;
       if (b & 1)
           p = p * a % MOD;
       return p;
   }

ll mod_inv(ll n) {
   return mod_pow(n, MOD - 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll v, x, m;
    cin >> v >> x >> m;
    MOD = m;
    ll invv = mod_inv(v);
    ll p = 0, q = 0;
    while (p < m) {
        q = (p * invv)%m;
        if (q != 0 && x == p/q) break;
        p++;
    }
    if (p < m && q < m) cout << p << " " << q << nl;
    else cout << -1 << nl;
    return 0;
}
