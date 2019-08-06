#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#define MOD 998244353

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    cin >> n;
    long long a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long exp, x, ans = 0;
    for (int i = 0; i < n; i++) {
        x = 0;
        exp = 1;
        while (a[i]) {
            x = (x + (exp*(a[i]%10)) % MOD) % MOD;
            exp = (exp*100) % MOD;
            a[i] /= 10;
        }
        x = (x * 11) % MOD;
        x = (n * x) % MOD;
        ans = (ans + x) % MOD;
    }
    cout << ans << endl;
    return 0;
}
