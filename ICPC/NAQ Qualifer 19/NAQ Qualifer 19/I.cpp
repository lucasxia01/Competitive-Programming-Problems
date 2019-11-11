#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cmath>
#define ll long long
#define INF 1LL<<40
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define F0Rd(i, n) for (int i = n-1; i >= 0; i--)

using namespace std;


int main() {
    int n, m, t, d, x;
    cin >> n >> m >> t >> d;
    int r[n+1];
    F0R(i, n+1) r[i] = 0;
    F0R(i, t) {
        cin >> x;
        r[x] = 1;
    }
    r[n] = 1;
    ll mat[n+1][n+1];
    FOR(i, 1, n) FOR(j, 1, n) mat[i][j] = INF;
    int v, w, c;
    F0R(i, m) {
        cin >> v >> w >> c;
        mat[v][w] = c;
        mat[w][v] = c;
    }
    FOR(k, 1, n) {
        FOR(i, 1, n) {
            FOR(j, 1, n) {
                if (mat[i][j] > mat[i][k] + mat[k][j]) {
                    mat[i][j] = mat[i][k] + mat[k][j];
                }
            }
        }
    }
    int s = 1;
    
    ll dist[n+1];
    FOR(i, 1, n) {
        dist[i] = INF;
    }
    dist[s] = 0;
    bool vis[n+1];
    FOR(i, 1, n) vis[i] = false;
    vis[s] = true;
    F0R(i, n-1) {
        ll minDist = INF;
        int idx = -1;
        FOR(i, 1, n) {
            if (r[i] && !vis[i]) {
                if (mat[s][i] <= d)
                    dist[i] = min(dist[i], dist[s] + mat[s][i]);
                if (minDist > dist[i]) {
                    idx = i;
                    minDist = dist[i];
                }
            }
        }
        if (idx == -1) break;
        vis[idx] = true;
        s = idx;
    }
    if (dist[n] != INF) cout << dist[n] << endl;
    else cout << "stuck" << endl;
    return 0;
}
