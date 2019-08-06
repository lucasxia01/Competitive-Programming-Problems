#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <utility>
#define MOD 998244353

using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int a[n+2];
    int large = -1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == n) large = i;
    }
    int i = large-1, j = large+1;
    a[0] = -2;
    a[n+1] = -2;
    int current = n-1;
    while (i >= 0 && j <= n+1) {
//        cout << i << " " << j << " " << current << endl;
//        cout << a[i] << " " << a[j] << endl;
        if (a[i] != current && a[j] != current) {
            break;
        }
        if (a[i]==current) i--;
        if (a[j]==current) j++;
        
        current--;
        
    }
    //cout << large << endl;
    if (current != 0) cout << "NO" << endl;
    else cout << "YES" << endl;
    
    return 0;
}
