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
#define FOR(i,a,b) for (int i = a; i <= b; i++)
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
    int x, y, t, l, w;
    int mat[1001][1001];
    queue<int> qx, qy, qt;
    while (1) {
        cin >> x;
        if (x == -1) break;
        cin >> y >> t >> l >> w;
        F0R(i, x+1) F0R(j, y+1) mat[i][j] = 0;
        int X, Y;
        F0R(i, l) {
            cin >> X >> Y;
            qx.push(X);
            qy.push(Y);
            qt.push(1);
            mat[X][Y] = 1;
        }
        int x0, x1, y0, y1;
        F0R(i, w) {
            cin >> x0 >> y0 >> x1 >> y1;
            if (x0 == x1) {
                FOR(j, min(y0, y1), max(y0, y1)) {
                    mat[x0][j] = 2;
                }
            } else if (y0 == y1) {
                FOR(j, min(x0, x1), max(x0, x1)) {
                    mat[j][y0] = 2;
                }
            } else {
                if ((x0 >= x1 && y0 >= y1) || (x0 <= x1 && y0 <= y1)) {
                    int k = min(y0, y1);
                    FOR(j, min(x0, x1), max(x0, x1)) {
                        mat[j][k] = 2;
                        k++;
                    }
                } else {
                    int k = max(y0, y1);
                    FOR(j, min(x0, x1), max(x0, x1)) {
                        mat[j][k] = 2;
                        k--;
                    }
                }
            }
        }
        int curX, curY, curT, nX, nY;
        int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
        int count = 0;
        while (!qx.empty() && qt.front() < t) {
            count++;
            curX = qx.front(); qx.pop();
            curY = qy.front(); qy.pop();
            curT = qt.front(); qt.pop();
            for (int d = 0; d < 4; d++) {
                nX = curX+dx[d]; nY = curY+dy[d];
                if (nX > 0 && nX <= x && nY > 0 && nY <= y && mat[nX][nY] == 0) {
                    qx.push(nX);
                    qy.push(nY);
                    qt.push(curT+1);
                    mat[nX][nY] = 1;
                }
            }
        }
        while (!qx.empty()) {
            qx.pop();
            qy.pop();
            qt.pop();
        }
        int ans = 0;
        FOR(i, 1, x) {
            FOR(j, 1, y) {
                //cout << mat[i][j];
                if (mat[i][j] == 1) ans++;
            }
            //cout << endl;
        }
        cout << ans << endl;
    }
    return 0;
}
