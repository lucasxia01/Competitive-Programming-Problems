#include <iostream>
#include <string>

typedef long long ll;
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll t, n, k;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        k--; // 0-indexed is always better
        int s = 0, c = 0;
        while (s <= k) { // make it go over by 1
            c++;
            s += c;
        }
        s -= c; // go back by 1
        c--;
        string ans(n, 'a');
        ans[n-1-(k-s)] = ans[n-2-c] = 'b';
        cout << ans << endl;
        
    }
    return 0;
}
