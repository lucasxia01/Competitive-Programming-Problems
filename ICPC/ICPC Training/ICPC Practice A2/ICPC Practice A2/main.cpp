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

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q, m;
    cin >> n;
    int a[n];
    rep(i, n) cin >> a[i];
    sort(a, a + n);
    cin >> q;
    rep(i, q) {
        cin >> m;
        cout << int(upper_bound(a, a + n, m) - a) << endl;
    }
    return 0;
}
