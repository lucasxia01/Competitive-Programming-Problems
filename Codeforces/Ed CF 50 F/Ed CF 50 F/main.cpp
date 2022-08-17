#include <iostream>
#include <set>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
#define llMAX LLONG_MAX
using namespace std;
ll power(ll x, ll p) {
    ll y = 1;
    while (p) {
        if (p % 2 == 1) {
            if (llMAX / y >= x) {
                y *= x;
                p--;
            }
        }
        x *= x;
        p /= 2;
    }
    return y;
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll n, a;
    cin >> n;
    int m[65];
    for (int i = 2; i < 65; i++) m[i] = 1;
    for (int i = 2; i < 65; i++) {
        for (int j = 2; j <= 64/i; j++) {
            if (i == j || m[i * j] == 0) m[i * j] = 0;
            else m[i * j] = -1 * m[i] * m[j];
        }
    }
    ll count = 0;
    rep(i, n) {
        cin >> a;
        count = 0;
        for (int j = 2; j < 65; j++) {
            ll x = pow((long double) a, (long double) 1.0/j) + 1;
            //cout << "hi " << j << " "  << x << " " << pow(x, j) << endl;
            while (1LL * pow((long double) x, (long double) j) > a) x--;
            //cout << j << " "  << x << endl;
            if (x == 1) break;
            count += (x - 1) * m[j];
        }
        cout << a - count - 1 << endl;
    }
    return 0;
}
