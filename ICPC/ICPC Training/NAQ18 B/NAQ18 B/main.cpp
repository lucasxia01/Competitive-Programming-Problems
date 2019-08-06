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
#include <numeric>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
#define MAX_N 1000011
#define INF (1<<29) + 123

using namespace std;

int g(int a, int b) {
    if (a < b) swap(a, b);
    if (b == 0) return a;
    return g(a % b, b);
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int p, q, s;
    cin >> p >> q >> s;
    if ((p * q)/g(p, q) <= s) cout << "yes" << endl;
    else cout << "no" << endl;
    return 0;
}
