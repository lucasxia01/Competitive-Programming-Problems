#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int t, n;
    cin >>t ;
    while(t) {
        cin >> n;
        int a[n];
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        int ans = min(a[n-2]-1, n-2);
        if (ans < 0) ans = 0;
        cout << ans << endl;
        t--;
    }
    
    return 0;
}
