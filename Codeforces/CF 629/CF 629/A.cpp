#include <iostream>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t, a, b;
    cin >> t;
    while (t--) {
        cin >> a >> b;
        if (a%b) cout << b-(a%b) << endl;
        else cout << 0 << endl;
    }
    return 0;
}
