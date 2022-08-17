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
#include <random>
#include <chrono>
#include <cassert>

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
#define sz(x) (int)x.size()

const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    int ans[n][n];
    int three[3][3] = {{1, 2, 6}, {9, 3, 7}, {5, 4, 8}};
    if (n < 3) {
        cout << -1 << endl;
        return 0;
    }
    F0R(i, 3) F0R(j, 3) ans[i][j] = three[i][j]+n*n-9;
    int count = 1;
    FOR(i, 3, n-1) { // this will go in a snake pattern and always end at the left column or top row, which means the rook/queen will then to go the top left corner of the 3x3
        if (i%2) {
            F0R(x, i+1) {
                ans[x][i] = count;
                count++;
            }
            F0Rd(y, i) {
                ans[i][y] = count;
                count++;
            }
        } else {
            F0R(x, i+1) {
                ans[i][x] = count;
                count++;
            }
            F0Rd(y, i) {
                ans[y][i] = count;
                count++;
            }
        }
    }
    F0R(i, n) {
        F0R(j, n) cout << ans[i][j] << " ";
        cout << '\n';
    }
    return 0;
}
