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
const int MX = 1<<20;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ld w, h;
    int n;
    cin >> w >> h >> n;
    h = h/w;
    ld x[n+1], cost[n+1];
    cost[0] = (1+h)*(1+h)/4;
    FOR(i, 1, n) {
        // cost[i-1] * x^2 + (((1-h)^2-2h^2) x^2 + 2(h^2-1)x + (1+h)^2)/4 = cost[i]
        // 2x (4cost[i-1] + (1-h-h^2)) + (2h^2-2) = 0
        // x = (1-h^2)/(h+h^2-1-4*cost[i-1])
        x[i] = (1-h*h)/(4*cost[i-1] + (h-1)*(h-1) - 2*h*h);
        cost[i] = cost[i-1]*x[i]*x[i] + (x[i]*x[i]*((h-1)*(h-1)-2*h*h) + 2*x[i]*(h*h-1) + (h+1)*(h+1))/4;
    }
    cout.precision(8);
    cout << fixed << cost[n]*w*w << endl;
    ld curX = w;
    vector<ld> ans;
    FORd(i, 1, n) {
        curX *= x[i];
        if (i <= 10) {
            ans.pb(curX);
        }
    }
    F0Rd(i, sz(ans)) {
        cout << fixed << ans[i] << endl;
    }
}
