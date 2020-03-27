#include <iostream>
#include <string>

#define F0R(i,n) for (int i = 0; i < n; i++)

typedef long long ll;
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll t, n, k;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        k--;
        int s = 0, c = 0;
        while (s <= k) {
            c++;
            s += c;
        }
        s -= c;
        c--;
        string ans = "";
        F0R(i, n) ans += 'a';
        ans[n-1-(k-s)] = ans[n-2-c] = 'b';
        cout << ans << endl;
        
    }
    return 0;
}
