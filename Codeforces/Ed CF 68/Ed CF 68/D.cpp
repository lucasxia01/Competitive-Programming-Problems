#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long q, n, k;
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> n >> k;
        if (k % 3 != 0) {
            if (n % 3 != 0) cout << "Alice" << endl;
            else cout << "Bob" << endl;
        } else {
            long long mod = n % (k+1);
            if (mod % 3 == 0 && mod != k) cout << "Bob" << endl;
            else cout << "Alice" << endl;
        }
    }
    return 0;
}
