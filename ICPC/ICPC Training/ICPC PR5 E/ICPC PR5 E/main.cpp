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

#define ll long long
#define ld long double
#define rep(i,n) for (int i = 0; i < n; i++)
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
    ll n, X;
    ld V;
    cin >> n >> X >> V;
    ld l[n], r[n], v[n];
    cout << n << endl;
    rep(i, n) { cin >> l[i] >> r[i] >> v[i]; cout << i << " " << v[i] << endl;}
    cout << "hi " << endl;
    assert(false);
    ld sum1 = 0;
    rep(i, n) sum1 += (l[i] - r[i]) * v[i]/ V;
    cout << sum1 << endl;
    
    ld Vsin = abs((ld) sum1 );
    if (Vsin * Vsin * 4 > V * V * 3) { cout << "Too hard" << endl; return 0;}
    ld Vcos = sqrt(V * V - Vsin * Vsin);
    cout << Vsin  << " " << Vcos << endl;
    cout.setf(ios::fixed);
    cout.precision(3);
    double ans = (double) X/(Vcos);
    if (Vcos * 2 < V) cout << "Too hard" << endl;
    else printf("%.3f\n", ans);
    return 0;
}
