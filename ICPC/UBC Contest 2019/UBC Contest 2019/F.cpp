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
    int p[n][2];
    F0R(i, n) F0R(j, 2) cin >> p[i][j];
    int count[n][n][2];
    F0R(i, n) F0R(j, n) { // i and j form the line
        if (i == j) {
            count[i][j][0] = count[i][j][1] = -1;
            continue;
        }
        count[i][j][0] = count[i][j][1] = 0;
        F0R(k, n) { //  for each point, we want which side of the line
            ll temp = (p[i][1]-p[j][1])*(p[k][0]-p[i][0])+(p[i][0]-p[j][0])*(p[i][1] - p[k][1]);
            if (k != i && k != j && temp > 0) count[i][j][0]++;
            if (k != i && k != j && temp < 0) count[i][j][1]++;
            if (k != i && k != j && temp == 0) // special case for points on the line
                if ((p[k][0]-p[i][0])*(p[k][0]-p[j][0]) <= 0 && (p[k][1]-p[i][1])*(p[k][1]-p[j][1]) <= 0) {
                    count[i][j][0]++;
                    count[i][j][1]++;
                } // if in between, it's on both sides; otherwise, its on neither
        }
    }
    ld ans[n];
    F0R(i, n) {
        ans[i] = (ld) 2/((i+3)*(i+2)*(i+1)); // precomputing probabilities
    }
    F0R(i, n) {
        ld ret = 0;
        F0R(j, n) F0R(k, j) {
            int d = (p[j][1]-p[k][1])*(p[i][0]-p[j][0])+(p[j][0]-p[k][0])*(p[j][1]-p[i][1]); // the area
            if (d == 0) continue;
            bool b = d > 0;
            ret += 0.5 * abs(d) * ans[count[j][k][!b]-1]; // -1 for current point
        }
        cout << fixed;
        cout << setprecision(8) << ret << endl;
    }
    return 0;
}
