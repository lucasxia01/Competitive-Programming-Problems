#include <iostream>
using namespace std;

int main() {
    int T, n, k, ans = 0, a, b;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> n >> k;
        ans = 0;
        for (int j = 0; j < k; j++) {
            cin >> a >> b;
            ans += (b - a + 1) % 2;
        }
        if (ans % 2 == 0) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
