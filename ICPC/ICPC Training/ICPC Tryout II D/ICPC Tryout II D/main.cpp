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

ll x[1011], y[1011], r[1011], m[1011][1011], n;
int mark[1011];
void dfs(int i, int p) {
    if (mark[n - 1] == 3) return;
    if (mark[i] != -1) {
        if (mark[i] != p) {
            mark[n - 1] = 3;
        }
        return;
    }
    mark[i] = p;
    rep (j, n) {
        if (m[i][j] == 1) {
            dfs(j, 3 - p);
        }
    }
    
}
ll gcd(ll a, ll b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return gcd(min(a, b), max(a, b) % min(a, b));
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    rep(i, n) cin >> x[i] >> y[i] >> r[i];
    rep (i, n) rep(j, n) if ((r[i] + r[j])*(r[i] + r[j]) == (x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j])) m[i][j] = 1;
    rep(i, n) mark[i] = -1;
    dfs(0, 1);
    if (mark[n - 1] == 3) cout << -1 << endl;
    else if (mark[n - 1] == -1) cout << 0 << endl;
    else {
        ll g = gcd(r[n-1], r[0]);
        cout << r[n - 1]/g << " " << -1 * (mark[n - 1] * 2 - 3) * r[0]/g << endl;
    }
    return 0;
}
