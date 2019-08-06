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

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n;
    int count = 0;
    int dir = 0;
    int ans = 0;
    int a[370] = {};
    rep(i, n) {
        cin >> k;
        a[k - 1]++;
    }
    rep(i, 365) {
        dir+=count;
        if (a[i]) count++;
        if (dir + count > 19) {
            count = 0;
            dir = 0;
            ans++;
            //cout << i + 1 << endl;
        }
        //cout << i + 1 << " " << dir << " " << count << endl;
    }
    if (dir || count) ans++;
    cout << ans << endl;
    return 0;
}
