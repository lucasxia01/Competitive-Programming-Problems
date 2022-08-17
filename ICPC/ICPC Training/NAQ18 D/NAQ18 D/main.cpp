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

int m[MAX_N][3], x, y, l, w, p;

bool check (int t) {
    // y is lane
    if (y == -1) return true;
    int o = m[y][0];
    int g = m[y][1];
    int s = m[y][2];
    int pos = s * t + o;
    if (y % 2) pos = w - pos - 1;
    //cout << x << " " << y << " " << pos << " " << t << endl;
    for (int i = pos; i >= pos - s + 1; i--) {
        //cout << "hi " << i << endl;
        if ((i % g) == (x % g)) {
            return false;
        }
    }
    return true;
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> l >> w;
    rep(i, l) cin >> m[i][0] >> m[i][1] >> m[i][2];
    cin >> p;
    string dirs;
    cin >> dirs;
    x = p;
    y = l;
    bool k = true;
    rep (i, dirs.length()) {
        char c = dirs[i];
        if (c == 'U') y--;
        else if (c == 'D') y++;
        else if (c == 'L') x--;
        else x++;
        k = check(i + 1);
        if (!k) {
            cout << "squish" << endl;
            return 0;
        } else if (y == -1) break;
    }
    if (y > -1) cout << "squish" << endl;
    else cout << "safe" << endl;
    return 0;
}
