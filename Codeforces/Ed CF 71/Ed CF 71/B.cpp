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
    int n, m;
    cin >> n >> m;
    int matA[n][m], matB[n][m];
    F0R(i, n) F0R(j, m) {
        cin >> matA[i][j];
        matB[i][j] = 0;
    }
    string output = "";
    int count = 0;
    F0R(i, n) F0R(j, m) {
        bool good = true;
        F0R(x, 2) F0R(y, 2) {
            if ((i+x >= n || j+y >= m) || matA[i+x][j+y] == 0) {
                good = false;
                break;
            }
        }
        if (good) {
            F0R(x, 2) F0R(y, 2) {
                matB[i+x][j+y] = 1;
            }
            output += to_string(i+1) + " " + to_string(j+1) + "\n";
            count++;
        }
    }
    F0R(i, n) F0R(j, m) {
        if (matA[i][j] != matB[i][j]) {
            output = "-1\n";
            break;
        }
    }
    if (output != "-1\n") output = to_string(count) + "\n" + output;
    cout << output;
    return 0;
}
