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
    long long w, h;
    cin >> w >> h;
    long long ans = 1;
    for (int i = 0; i < w + h; i++) {
        ans = (ans * 2) % MOD;
    }
    cout << ans << endl;
    
    return 0;
}
