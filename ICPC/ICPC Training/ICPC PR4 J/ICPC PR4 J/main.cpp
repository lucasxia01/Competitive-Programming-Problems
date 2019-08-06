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
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define MAX_N 1000011
#define INF (1<<29) + 123

using namespace std;

ll a[10][2];
ll b[10][3];
ll curT = 0;

ll nextTime(ll t, ll i) {
    // if machine dude has not started yet
    if (t < b[i][2]) {
        t += a[i][0];
        b[i][2] = max(b[i][2], t);
        return t;
    }
    
    // x is where the dude is in his cycle
    ll x = (t - b[i][2]) % (b[i][0] + b[i][1]);
    ll y = (t - b[i][2]) / (b[i][0] + b[i][1]);
    // if john has to wait for dude
    b[i][2] += y * (b[i][0] + b[i][1]);
    if (x < b[i][0]) {
        t += (b[i][0] - x) + a[i][0];
    } else {// dude is in recovery
        t += a[i][0];
    }
    b[i][2] = max(b[i][2] + (b[i][0] + b[i][1]), t);
    return t;
    
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    rep(i, 10) rep(j, 2) cin >> a[i][j];
    rep(i, 10) rep(j, 3) cin >> b[i][j];
    rep(j, 3) {
        rep(i, 10)   {
            curT = nextTime(curT, i) + a[i][1];
            //cout << i << " " << j << " " << curT << endl;
        }
//        rep(i, 10) cout << b[i][2] << " ";
//        cout << endl;
    }
    cout << curT - a[9][1] << endl;
    return 0;
}
