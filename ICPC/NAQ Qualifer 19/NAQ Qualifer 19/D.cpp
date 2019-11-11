#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cmath>
#define ll long long

#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; i++)

using namespace std;

int main() {
    int n, x;
    cin >> n;
    int large = 0;
    int a[201] = {};
    F0R(i, n) {
        cin >> x;
        a[x] = 1;
        large = max(large, x);
    }
    bool none = true;
    FOR(i, 1, large) {
        if (a[i] == 0) {
            none = false;
            cout << i << endl;
        }
    }
    if (none) cout << "good job" << endl;
    return 0;
}
