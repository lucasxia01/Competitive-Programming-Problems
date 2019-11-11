#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cmath>
#include <tgmath.h>

#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; i++)

using namespace std;

int main() {
    int n;
    cin >> n;
    int p[n];
    F0R(i, n) cin >> p[i];
    sort(p, p+n);
    long double exp = 0;
    long double dist[101][101] = {};
    dist[0][0] = 1;
    long double cur = 0, ans = 0;
    for (int i = n-1; i >= 0; i--) {
        cur = 0;
        for (int j = 0; j <= n-i; j++) {
            dist[n-i][j] = (long double)(100-p[i])/100 * dist[n-i-1][j];
            if (j > 0) dist[n-i][j] += (long double) p[i]/100 * dist[n-i-1][j-1];
            //cout << n-i << " " << j << " " << dist[n-i][j] << endl;
            if (j == 0) continue;
            exp = (long double) j/(n-i);
            //cout << j << " " << exp << " " << pow(j, exp) << endl;
            cur += dist[n-i][j] * powl(j, exp);
        }
        //cout << cur << " " << prev << endl;
        //if (cur <= prev) break;
        if (cur > ans) ans = cur;
    }
    cout.precision(15);
    cout << ans << endl;
    return 0;
}
