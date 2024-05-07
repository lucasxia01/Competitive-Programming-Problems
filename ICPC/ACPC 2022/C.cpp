#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

ll MAX = 1e9;
int main() {
    int n; cin >> n;
    ll ans = 0;
    bool ok = 1;
    for (int i = 1; i <= n; i++) {
        ll tmp = 1;
        for (int j = n; j > n-i; j--) {
            tmp *= j;
            if (tmp > MAX) {
                ok = 0;
                break;
            }
        }
        ans += tmp;
        if (ans > MAX) {
            ok = 0;
            break;
        }
        if (!ok) break;
    }
    if (!ok) {
        cout << "JUST RUN!!" << endl;
    } else cout << ans << endl;
}