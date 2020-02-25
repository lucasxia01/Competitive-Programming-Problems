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

int fenw[2*MAX_N];
int n;
void mod(int i, int v) {
    while (i <= n) {
        fenw[i] += v;
        i += i&-i;
    }
}

int query(int i) {
    int sum = 0;
    while (i > 0) {
        sum += fenw[i];
        i -= i&-i;
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    vpi p;
    int x[n], v[n];
    F0R(i, n) cin >> x[i];
    F0R(i, n) {
        cin >> v[i];
        p.pb(mp(v[i], x[i]));
    }
    // coord compress
    unordered_map<int, int> m;
    int rev_map[n];
    sort(x, x+n);
    F0R(i, n) {
        //printf("%d %d\n", x[i], i+1);
        m[x[i]] = i+1;
        rev_map[i] = x[i];
    }
    F0R(i, n) {
        p[i].s = m[p[i].s];
    }
    sort(p.begin(), p.end());
    ll ans = 0;
    F0R(i, n) {
        int q = query(p[i].s);
        //cout << p[i].s << " " << q << endl;
        ans +=  1LL*q * rev_map[p[i].s-1];
        ans -= 1LL*((n-i-1)-(p[i].s-1-q)) * rev_map[p[i].s-1];
        mod(p[i].s, 1);
    }
    cout << ans << endl;
    
    return 0;
}
