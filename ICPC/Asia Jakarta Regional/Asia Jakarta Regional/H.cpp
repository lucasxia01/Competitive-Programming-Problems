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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    ld ans = 0;
    pair<ll, ll> l[n];
    ll areas[n];
    F0R(i, n) {
        cin >> l[i].f >> l[i].s;
        if (l[i].f < l[i].s) swap(l[i].f, l[i].s);
        areas[i] = l[i].f*l[i].s;
    }
    sort(l, l+n);
    sort(areas, areas+n);
    ans = (long double)areas[n-1]/2;
    if (n != 1) {
        ll cur1 = l[n-1].f, cur2 = l[n-1].s, temp1 = cur1, temp2 = cur2;
        F0Rd(i, n-1) {
            temp1 = cur1; temp2 = cur2;
            if (temp1 > l[i].f) temp1 = l[i].f;
            if (temp2 > l[i].s) temp2 = l[i].s;
            if (ans < temp1*temp2) ans = temp1*temp2;
            if (l[i].s > cur2) {
                cur1 = l[i].f;
                cur2 = l[i].s;
            }
        }
    }
    cout << fixed << setprecision(1) << ans << endl;
    
    return 0;
}
