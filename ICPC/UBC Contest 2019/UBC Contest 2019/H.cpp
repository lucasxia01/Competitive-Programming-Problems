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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll c;
    cin >> c;
    const ll NUM = 2100000;
    bool prime[NUM]; F0R(i, NUM) prime[i] = true;
    vector<ll> primes;
    for (ll i = 2; i < NUM; i++) {
        if (prime[i]) {
            primes.pb(i);
            for (ll j = 2*i; j < NUM; j+=i) {
                prime[j] = false;
            }
        }
    }
    int count = 0;
    ll ans = 1;
    for (vector<ll>::iterator it = primes.begin(); it != primes.end();) {
        if (c % *it == 0) {
            count++;
            c /= *it;
        } else {
            if (count % 2) ans *= *it;
            it++;
            count = 0;
        }
    }
    ll SQRT = sqrt(c);
    if (SQRT*SQRT == c) {
        c = 1;
    }
    cout << ans*c << endl;
    return 0;
}
