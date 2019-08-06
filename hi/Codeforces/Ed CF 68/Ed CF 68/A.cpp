#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n, l, x;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> l >> x;
        cout << 2*x << endl;
    }
    return 0;
}
