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
    string s;
    cin >> s;
    int ans[10][10] = {};
    int minSteps[10][10][10] = {};
    F0R(diff, 10) {
        F0R(i, 10) {
            F0R(j, 10) {
                // (a,b,c) = (i,j,diff)
                int minStep = 19;
                F0R(x, 10) {
                    F0R(y, 10) {
                        if (x+y > 0 && (i*x+j*y)%10 == diff%10) {
                            minStep = min(minStep, x+y);
                        }
                    }
                }
                if (minStep == 19) minSteps[diff][i][j] = -1;
                else minSteps[diff][i][j] = minStep-1;
            }
        }
    }
    F0R(i, 10) {
        F0R(j, 10) {
            //cout << minSteps[2][i][j] << " ";
            ans[i][j] = 0;
        }
        //cout << endl;
    }
    F0R(k, (int)s.length()) {
        if (k == 0) continue;
        F0R(i, 10) {
            F0R(j, 10) {
                if (ans[i][j] == -1) continue;
                if (minSteps[(s[k]-s[k-1]+10)%10][i][j] == -1) {
                    ans[i][j] = -1;
                    continue;
                }
                ans[i][j] += minSteps[(s[k]-s[k-1]+10)%10][i][j];
            }
        }
    }
    F0R(i, 10) {
        F0R(j, 9) cout << ans[i][j] << " ";
        cout << ans[i][9] << endl;
    }
    return 0;
}
