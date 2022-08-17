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

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
#define MAX_N 1000011
#define INF (1<<29) + 123

using namespace std;
int dp[503][503];
int a[503][503];
bool mark[503][503];
int n, m;

void bfs(int x0, int y0, int move0) {
    queue<int> qx, qy, qm;
    qx.push(x0);
    qy.push(y0);
    qm.push(move0);
    int x, y, move;
    while (qx.size() > 0) {
        x = qx.front();
        qx.pop();
        y = qy.front();
        qy.pop();
        move = qm.front();
        qm.pop();
        //cout << x << " " << y << endl;
        if (x < 0 || x >= n || y < 0 || y >= m) continue;
        if (move >= dp[x][y]) continue;
        dp[x][y] = move;
        mark[x][y] = true;
        int v = a[x][y];
        if (v == 0) continue;
        qx.push(x - v);
        qy.push(y);
        qm.push(move + 1);
        qx.push(x + v);
        qy.push(y);
        qm.push(move + 1);
        qx.push(x);
        qy.push(y - v);
        qm.push(move + 1);
        qx.push(x);
        qy.push(y + v);
        qm.push(move + 1);
    }
   
    
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    char c;
    rep(i, n) {
        rep (j, m) {
            cin >> c;
            a[i][j] = c - '0';
            dp[i][j] = INF;
            mark[i][j] = false;
        }
    }
    bfs(0, 0, 0);
    if (dp[n - 1][m - 1] == INF) cout << -1 << endl;
    else cout << dp[n - 1][m - 1] << endl;
    return 0;
}
