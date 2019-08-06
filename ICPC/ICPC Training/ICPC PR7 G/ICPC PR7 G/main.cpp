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

long double m (long double a, long double b, long double c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    long double a, b, c;
    cin >> a >> b >> c;
    if (m(a, b, c) * 2 >= a + b + c) {
        cout << -1 << endl;
        return 0;
    }
    long double area = a * a * sqrt(3)/4 + b * b * sqrt(3)/4 + c * c * sqrt(3)/4;
    long double s = (a + b + c)/2;
    long double area2 = sqrt(s) * sqrt(s - a) * sqrt(s - b) * sqrt(s - c);
    area += 3 * area2;
    cout.precision(9);
    cout.setf(ios::fixed);
    cout << area/2 << endl;
    return 0;
}
