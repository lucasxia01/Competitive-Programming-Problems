#include <iostream>

using namespace std;

const int MOD = 24*60;
const int MX = MOD+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    int a[n];
    int count[MX] = {};
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        count[a[i]]++;
    }
    int ans = n;
    for (int k = 1; k < MOD; k++) {
        int curAns = n;
        for (int i = 0; i < MOD; i++)
            if (i >= k) curAns -= min(count[i-k], count[i]);
        ans = min(ans, curAns);
    }
    cout << ans << ' ' << n << '\n';
    return 0;
}
