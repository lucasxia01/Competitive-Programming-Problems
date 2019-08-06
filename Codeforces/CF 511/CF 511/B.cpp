#include <iostream>
#include <set>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <string>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
using namespace std;

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int m = 0;
    int x, y;
    rep (i, n) {
        cin >> x >> y;
        m = max(m, x + y);
    }
    cout << m << endl;
    return 0;
}
