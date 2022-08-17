#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    long long T, n, ans = 0;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> n;
        long long a[510000];
        ans = 0;
        for (int j = 0; j < n * (n + 1)/2; j++) {
            cin >> a[j];
        }
        sort(a, a + (n * (n + 1)/2));
        for (int j = 0; j < n; j++) {
            for (int k = 0; k <= j; k++) {
                //cout << a[(j*(j+1)/2) + k] << " ";
                ans += (n - j - 1) * a[(j*(j+1)/2) + k];
                
            }
        }
        cout << ans % 1000000007 << endl;
    }
    return 0;
}
