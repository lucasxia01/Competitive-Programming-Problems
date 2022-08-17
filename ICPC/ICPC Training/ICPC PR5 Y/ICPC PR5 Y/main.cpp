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
    double k, p, x;
    cin >> k >> p >> x;
    double m = sqrt(k * p/x);
    int a = (int) m, b = (int) m + 1;
    //cout << a << " " << b << endl;
    double ans = min(k/a * p + x * a, k/b * p + x * b);
    cout.precision(3);
    cout.setf(ios::fixed);
    cout << ans << endl;
    return 0;
}
