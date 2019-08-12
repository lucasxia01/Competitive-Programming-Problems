#include <iostream>
#include <set>
#include <utility>
#include <cmath>
#include <cstdlib>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
using namespace std;

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll l, r;
    cin >> l >> r;
    cout << "YES" << endl;
    for (ll i = l; i <= r; i+=2) {
        cout << i << " " << i + 1 << endl;
    }
    return 0;
}
