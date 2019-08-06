#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n, k, x;
    cin >> n >> k;
    int count[k];
    for (int i = 0; i < k; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        cin >> x;
        count[x-1]++;
    }
    sort(count, count+k);
    int ans = 0;
    for (long long i = k-1; i >= 0; i--) {
        if (count[i] % 2 != 0) ans++;
    }
    cout << n - ans + (ans+1)/2 << endl;
    return 0;
}
