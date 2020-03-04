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
int n;
char mat[1000][1000];
pi e[1000][1000];

int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
char dC[4] = {'U', 'L', 'D', 'R'};

void dfs(int cX, int cY, int eX, int eY) {
    //cout << cX << " " << cY << " " << eX << " " << eY << " " << mat[cX][cY] << endl;
    int x, y;
    F0R(d, 4) {
        x = cX + dx[d];
        y = cY + dy[d];
        if (x < 0 || x >= n || y < 0 || y >= n) continue;
        //cout << x << " " << y << " " << mat[x][y] << endl;
        if (e[x][y].f == eX && e[x][y].s == eY && !mat[x][y]) {
            mat[x][y] = dC[d];
            dfs(x, y, eX, eY);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    F0R(i, n) F0R(j, n) {
        cin >> e[i][j].f >> e[i][j].s;
        e[i][j].f--;
        e[i][j].s--;
        if (e[i][j].f == i && e[i][j].s == j) {
            mat[i][j] = 'X';
        } else mat[i][j] = 0;
    }
    F0R(i, n) F0R(j, n) {
        if (mat[i][j] == 'X') {
            dfs(i, j, i, j);
        } else if (e[i][j].f == -2 && e[i][j].s == -2) {
            int x, y;
            F0R(d, 4) {
                x = i + dx[d];
                y = j + dy[d];
                if (x < 0 || x >= n || y < 0 || y >= n) continue;
                if (e[x][y].f == -2 && e[x][y].s == -2) {
                    mat[i][j] = dC[(d+2)%4];
                }
            }
        }
    }
    F0R(i, n) F0R(j, n) {
        if (mat[i][j] == 0) {
            cout << "INVALID" << endl;
            return 0;
        }
    }
    cout << "VALID" << endl;
    F0R(i, n) {
        F0R(j, n) {
            cout << mat[i][j];
        }
        cout << endl;
    }
    return 0;
}
