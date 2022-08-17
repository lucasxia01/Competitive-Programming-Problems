#include <iostream>
#include <set>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <string>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
using namespace std;

int n, m;

int f(int a, int b) {
    return a * m + b * n - 2 * a * b;
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int k;
    cin >> n >> m >> k;
    rep (i, n + 1) {
        rep(j, m + 1) {
            if (f(i, j) == k) {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
    return 0;
}
