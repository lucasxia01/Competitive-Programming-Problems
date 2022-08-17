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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t, n, m;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        int a[n], c[n], p[m];
        F0R(i, n) {
            cin >> a[i];
            c[i] = a[i];
        }
        F0R(i, m) cin >> p[i];
        sort(p, p+m);
        sort(a, a+n);
        int prev = p[0]-1;
        bool ok = true;
        FOR(i, 1, m) {
            if (i == m || p[i-1]+1 != p[i]) {
                //printf("%d %d\n", prev, p[i-1]);
                sort(c+prev, c+p[i-1]+1);
                if (i != m) prev = p[i]-1;
            }
        }
        F0R(i, n) {
            //cout << c[i] << " ";
            if (c[i] != a[i]) ok = false;
        } //cout << endl;
        if (!ok) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
    return 0;
}
