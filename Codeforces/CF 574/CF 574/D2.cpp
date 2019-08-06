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
    sort(a, a + n);
    long long pos[11][2] = {};
    for (int i = 1; i <= 10; i++) {
        pos[i][0] = -10000;
        pos[i][1] = -10001;
    }
    long long exp = 1, x = 0, ans = 0;
    int length = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] >= exp && a[i] < exp*10) {
            exp *= 10;
            if (i != 0) pos[length][1] = i - 1;
            length++;
            pos[length][0] = i;
        } else if (a[i] >= exp) {
            exp*=10;
            length++;
            i--;
        }
    }
    pos[length][1] = n - 1;
    
//    for (int i = 1; i < 10; i++) {
//        cout << pos[i][0] << " " << pos[i][1] << endl;
//    }
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            for (long long k = pos[i][0]; k <= pos[i][1]; k++) {
                x = 0;
                exp = 10;
                int count = 0;
                long long temp = a[k];
                while (temp) {
                    x = (x + (exp*(temp%10)) % MOD) % MOD;
                    count++;
                    if (count < j) exp = (exp*100) % MOD;
                    else exp = (exp*10) % MOD;
                    temp /= 10;
                }
                x = (x * (pos[j][1] - pos[j][0] + 1)) % MOD;
                ans = (ans + x) % MOD;
            }
            //cout << i << " " << x << endl;
            for (long long k = pos[j][0]; k <= pos[j][1]; k++) {
                x = 0;
                exp = 1;
                int count = 0;
                long long temp = a[k];
                //cout << "k: " << k << endl;
                while (temp) {
                    x = (x + (exp*(temp%10)) % MOD) % MOD;
                    count++;
                    if (count <= i) exp = (exp*100) % MOD;
                    else exp = (exp*10) % MOD;
                    temp /= 10;
                }
                x = (x * (pos[i][1] - pos[i][0] + 1)) % MOD;
                ans = (ans + x) % MOD;
            }
            //cout << j << " " << x << endl;
        }
    }
    cout << ans << endl;
    return 0;
}
