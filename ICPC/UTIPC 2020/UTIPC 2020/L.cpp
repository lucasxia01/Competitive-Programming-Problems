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

const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

const ll MX = 1e15+5;
const ll sqrtMX = sqrt(MX);
ll m;
ll gcd(ll a, ll b) {
    if (a > b) return gcd(b, a);
    if (a == 0) return b;
    return gcd(b%a, a);
}

ll calc(ll b) {
    ll t = b;
    ll count = 1;
    while (2*t < m) t*=2, count++;
    ll ret = count*m - ((t/b)*2-1)*b;
    // cout << b << " " << ret << endl;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n >> m;
    ll g = 0;
    ll a[n];
    F0R(i, n) {
        cin >> a[i];
        g = gcd(g, a[i]-1);
    }
    ll d = g;
    while (d%2==0) d/=2;
    ll ans = 0;
    for (ll i = 1; i <= min(m-1, (ll)sqrt(d)+1); i+=2) {
        if (d%i) continue;
        ans += calc(i);
        if (i*i == d) continue;
        ans += calc(d/i);
    }
    cout << ans << '\n';
    return 0;
}
