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
    int n;
    cin >> n;
    char mat[n][n];
    F0R(i, n) F0R(j, n) cin >> mat[i][j];
    string s;
    cin >> s;
    char ans[n][n];
    F0R(i, n) F0R(j, n) ans[i][j] = '.';
    int X = 0, Y = 0, idx = 0;
    bool ok = true;
    F0R(i, 4) {
        F0R(x, n) {
            F0R(y, n) {
                if (i == 0) {
                    X = x;
                    Y = y;
                } else if (i == 1) {
                    X = n-1-y;
                    Y = x;
                } else if (i == 2) {
                    X = n-1-x;
                    Y = n-1-y;
                } else if (i == 3) {
                    X = y;
                    Y = n-1-x;
                }
                if (mat[X][Y] == '.') {
                    ans[x][y] = s[idx];
                    if (idx == s.length()) {
                        ok = false;
                        y = n; x = n; i = 4;
                        break;
                    }
                    idx++;
                }
            }
        }
        
    }
    F0R(x, n) {
        F0R(y, n) {
            if (ans[x][y] == '.') ok = false;
        }
    }
    if (ok) {
        F0R(x, n) {
            F0R(y, n) {
                cout << ans[x][y];
            }
        }
        cout << endl;
    } else cout << "invalid grille" << endl;
    return 0;
}
