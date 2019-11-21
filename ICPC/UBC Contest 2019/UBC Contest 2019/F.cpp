#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
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
#include <iomanip>

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

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()
 
template<int sz> struct Combo {
    ll fac[sz + 1];
    ll ifac[sz + 1];
 
    Combo() {
        fac[0] = ifac[0] = 1LL;
        for (int i = 1; i <= sz; i++) {
            fac[i] = fac[i - 1] * i % MOD;
            ifac[i] = mod_inv(fac[i]);
        }
    }
 
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
 
    ll comb(ll n, ll r) {
        if (n < r || n < 0 || r < 0) return 0LL;
        ll res = (fac[n] * ifac[r] % MOD) * ifac[n - r] % MOD;
        return res;
    }
};
 
ll mod(ll x) {
    return (x % MOD + MOD) % MOD;
}
 
ll modAdd(ll x, ll y) {
    return ( (x % MOD + y % MOD) % MOD + MOD ) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    int p[n][2];
    F0R(i, n) F0R(j, 2) cin >> p[i][j];
    int count[n][n][2];
    F0R(i, n) F0R(j, n) {
        if (i == j) {
            count[i][j][0] = count[i][j][1] = -1;
            continue;
        }
        count[i][j][0] = count[i][j][1] = 0;
        //printf("%d %d, %d %d\n", p[i][0], p[i][1], p[j][0], p[j][1]);
        F0R(k, n) {
            ll temp = (p[i][1]-p[j][1])*(p[k][0]-p[i][0])+(p[i][0]-p[j][0])*(p[i][1] - p[k][1]);
            if (k != i && k != j && temp > 0) count[i][j][0]++;
            if (k != i && k != j && temp < 0) count[i][j][1]++;
            if (k != i && k != j && temp == 0)
                if ((p[k][0]-p[i][0])*(p[k][0]-p[j][0]) <= 0 && (p[k][1]-p[i][1])*(p[k][1]-p[j][1]) <= 0) {
                    count[i][j][0]++;
                    count[i][j][1]++;
                }
        }
        //cout << "above " << count[i][j][1] << ", and below " << count[i][j][0] << endl;
    }
    ld ans[n];
    F0R(i, n) {
        ans[i] = (ld) 2/((i+3)*(i+2)*(i+1));
    }
    F0R(i, n) {
        ld ret = 0;
        F0R(j, n) F0R(k, j) {
            //printf("%d %d, %d %d, %d %d\n", p[i][0], p[i][1], p[j][0], p[j][1], p[k][0], p[k][1]);
            int d = (p[j][1]-p[k][1])*(p[i][0]-p[j][0])+(p[j][0]-p[k][0])*(p[j][1]-p[i][1]);
            if (d == 0) continue;
            bool b = d > 0;
//            cout << "area " << d << endl;
//            cout << "count of same side " <<  count[j][k][!b] << " and other side " << count[j][k][b] << endl;
            ret += 0.5 * abs(d) * ans[count[j][k][!b]-1];
        }
        cout << fixed;
        cout << setprecision(8) << ret << endl;
    }
    return 0;
}
