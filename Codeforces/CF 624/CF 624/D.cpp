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
    int t, a, b, c;
    cin >> t;
    while (t--) {
        cin >> a >> b >> c;
        int minCost = INF;
        int x, y, z;
        int p = -1, q = -1, r = -1;
        int P = -1, Q = -1, R = -1;
        for (int B = 1; B <= 20000; B++) {
            y = abs(B-b);
            int C;
            if (c < B) {
                z = B-c;
                C = B;
            } else {
                z = min(c%B, B-(c%B));
                if (c%B < B-(c%B)) C = c - (c%B);
                else C = c + (B - (c%B));
            }
            for (int A = 1; A*A <= B; A++) {
                if (B % A == 0) {
                    x = abs(A-a);
                    if (minCost > x+y+z) {
                        p = x; q = y; r = z;
                        P = A; Q = B; R = C;
                        minCost = x+y+z;
                    }
                    x = abs(B/A-a);
                    if (minCost > x+y+z) {
                        p = x; q = y; r = z;
                        P = B/A; Q = B; R = C;
                        minCost = x+y+z;
                    }
                }
            }
        }
        cout << minCost << endl;
        printf("%d %d %d\n", P, Q, R);
        fflush(stdout);
    }
    return 0;
}
