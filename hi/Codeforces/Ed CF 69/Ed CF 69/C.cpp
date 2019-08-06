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
    int n, k;
    cin >> n >> k;
    long long a[n];
    long long diffs[n-1];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i != 0) {
            diffs[i-1] = a[i]-a[i-1];
        }
    }
    sort(diffs, diffs+(n-1));
    long long totalDiff = a[n-1]-a[0];
    for(int i = 0; i < k-1;i++) {
        totalDiff -= diffs[n-2-i];
    }
    cout << totalDiff << endl;
    
    
    return 0;
}
