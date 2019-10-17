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
    int n, m;
    cin >> n >> m;
    char mat[n][m];
    int ans[n][m];
    queue<int> x, y;
    F0R(i, m) {
        x.push(-1);
        y.push(i);
        x.push(n);
        y.push(i);
    }
    F0R(i, n) {
        x.push(i);
        y.push(-1);
        x.push(i);
        y.push(m);
    }
    F0R(i, n) F0R(j, m) {
        cin >> mat[i][j];
        if (mat[i][j] == '.') {
            ans[i][j] = 0;
            x.push(i);
            y.push(j);
        } else ans[i][j] = -1;
    }
    int cX, cY, X, Y;
    int dirX[4] = {1, 0, -1, 0}, dirY[4] = {0, 1, 0, -1};
    int maxAns = 1;
    while (!x.empty()) {
        cX = x.front(); x.pop();
        cY = y.front(); y.pop();
        for (int dir = 0; dir < 4; dir++) {
            X = cX + dirX[dir]; Y = cY + dirY[dir];
            if (X >= 0 && X < n && Y >= 0 && Y < m && ans[X][Y] == -1) {
                x.push(X);
                y.push(Y);
                if (cX >= 0 && cX < n && cY >= 0 && cY < m) ans[X][Y] = ans[cX][cY]+1;
                else ans[X][Y] = 1;
                maxAns = max(maxAns, ans[X][Y]);
            }
        }
    }
    if (maxAns < 10) {
        F0R(i, n) {
            F0R(j, m) {
                cout << ".";
                if (ans[i][j] == 0) cout << ".";
                else cout << ans[i][j];
            } cout << endl;
        }
    } else {
        F0R(i, n) {
            F0R(j, m) {
                cout << ".";
                if (ans[i][j] == 0) cout << "..";
                else if (ans[i][j] >= 10) cout << ans[i][j];
                else cout << "." << ans[i][j];
            } cout << endl;
        }
    }
    return 0;
}
