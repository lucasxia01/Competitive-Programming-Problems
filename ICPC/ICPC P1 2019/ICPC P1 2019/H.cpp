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
    cin.tie(0); cout.tie(0);
    int n, a, b, c, d;
    cin >> n;
    F0R(i, n) {
        ll ans = 0, temp = 0, temp1 = 0, x, y, z;
        cin >> a >> b >> c >> d;
        int s = min(a, min(b, c));
        int l = max(a, max(b, c));
        int m = a + b + c - s - l;
        if (d < m-s) {
            temp = (s+d)*(s+d) + m*m+l*l + 7*(s+d);
            temp1 = s*s + m*m + (l+d)*(l+d) + 7*s;
        } else if (d < (l-s) + (l-m)) {
            x = (s + m + d)/2;
            temp = x*x + (s+m+d-x)*(s+m+d-x)+l*l+7*(x);
            temp1 = m*m+m*m+(l+d-(m-s))*(l+d-(m-s))+7*m;
        } else {
            x = (s+m+l+d)/3;
            y = x; z = x;
            if ((s+m+l+d) % 3 >= 1) z++;
            if ((s+m+l+d) % 3 >= 2) y++;
            temp = x*x + y*y+z*z + 7*x;
            temp1 = 2*(l*l) + (l+d-(l-s)-(l-m))*(l+d-(l-s)-(l-m)) + 7*l;
        }
        if (temp > ans) ans = temp;
        if (temp1 > ans) ans = temp1;
        cout << ans << endl;
    }
    
    return 0;
}
