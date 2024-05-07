#include <bits/stdc++.h>
using namespace std;

double eps = 1e-8;
int main() {
    int n, t; cin >> n >> t;
    vector<array<double, 3> > v(n);
    double total = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> v[i][j];
        }
        total += v[i][2];
    }
    // bin search on z
    double lo = 0, hi = 1e6+1;
    while ((hi-lo) > eps) {
        double mid = (lo+hi)/2;
        double sum = 0;
        for (int i = 0; i < n; i++) {
            double tmp = v[i][2]/total * mid;
            tmp = max(tmp, v[i][0]);
            tmp = min(tmp, v[i][1]);
            sum += tmp;
        }
        if (sum <= t) lo = mid;
        else hi = mid;
    }
    cout.precision(8);
    for (int i = 0; i < n; i++) {
        double tmp = v[i][2]/total * lo;
        tmp = max(tmp, v[i][0]);
        tmp = min(tmp, v[i][1]);
        cout << tmp << '\n';
    }
}