#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int a[n]; for (int i = 0; i < n; i++) cin >> a[i];
    map<int, vector<int> > M;
    for (int i = 0; i < n; i++) {
        if (M.find(a[i]) == M.end()) {
            vector<int> tmp;
            M[a[i]] = tmp;
        }
        M[a[i]].push_back(i);
    }
    // precompute
    int q; cin >> q;
    while (q--) {
        int i; cin >> i; i--;
        int m; cin >> m;
        int b[m]; for (int j = 0; j < m; j++) cin >> b[j];
        // bin search for ans
        int lo = i, hi = n;
        while (lo < hi) {
            int mid = (lo+hi)/2;
            // count up to mid
            int sum = 0;
            for (int j = 0; j < m; j++) {
                sum += upper_bound(M[b[j]].begin(), M[b[j]].end(), mid) - upper_bound(M[b[j]].begin(), M[b[j]].end(), i-1);
            }
            // cerr << mid << " " << sum << endl;
            if (sum != mid-i+1) hi = mid;
            else lo = mid+1;
        }
        cout << lo-i << endl;
    }
}