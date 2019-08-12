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
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

ll gcd (ll a, ll b) {
    if (b == 0) return a;
    if (a < b) return gcd(b, a);
    return gcd(b, a % b);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll n, m, q;
    cin >> n >> m >> q;
    ll GCD = gcd(n, m);
    ll n1 = n/GCD;
    ll m1 = m/GCD;
    F0R(i, q) {
        ll s0, s1, e0, e1;
        cin >> s0 >> s1 >> e0 >> e1;
        s1--;
        e1--;
        if (s0 == 1) s1 = s1/n1;
        else s1 = s1/m1;
        if (e0 == 1) e1 = e1/n1;
        else e1 = e1/m1;
        if (s1 == e1) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    
    return 0;
}
