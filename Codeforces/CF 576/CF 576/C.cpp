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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll n, I;
    cin >> n >> I;
    ll a[n];
    map<ll, ll> m;
    F0R(i, n) {
        cin >> a[i];
        if (m.find(a[i]) == m.end()) {
            m.insert(make_pair(a[i], 1));
        } else {
            m[a[i]]++;
        }
    }
    ll maxClass = 8*I/n;
    ll pow = 1;
    F0R(i, maxClass) {
        pow*=2;
    }
    ll num = m.size() - pow;
    //cout << num << " " << m.size() << endl;
    if (num <= 0) {
        cout << 0 << endl;
        return 0;
    }
    ll changed = 0;
    int count = 0, i = 0;
    auto it = m.begin();
    for (; it != m.end() && i < pow; it++) {
        count += it->s;
        i++;
    }
    changed = count;
    auto it1 = m.begin();
    for (; it!=m.end(); it++) {
        count -= it1->s;
        count += it->s;
        if (count > changed) changed = count;
        it1++;
    }
    cout << n - changed << endl;
    return 0;
}
