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
    vector<pair<ld,ld>> v;
    ld x, y;
    F0R(i, n) {
        cin >> x >> y;
        v.pb(mp(x, y));
    }
    sort(v.begin(), v.end());
    ld ans = 0;
    F0R(i, n-1) {
        //printf("%Lf %Lf %Lf %Lf\n", v[i+1].s, v[i].s, v[i+1].f, v[i].f);
        if (abs(v[i].s - v[i+1].s)/(v[i+1].f-v[i].f) > ans) {
            ans = abs(v[i].s - v[i+1].s)/(v[i+1].f-v[i].f);
        }
    }
    cout << fixed;
    cout << setprecision(6) << ans << endl;
    
    return 0;
}
