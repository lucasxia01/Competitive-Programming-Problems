#include <bits/stdc++.h>

#define int long long
#define pi pair<int, int>
#define vi vector<int>
#define vpi vector<pi>
#define rep(i, a, b) for(int i = a; i < (b); i++)
using namespace std;

signed main() {
    int x; cin >> x;
    if (x == 1) {
        cout << 1 << endl;
        return 0;
    }
    rep(i, 2, 61) {
        // bin search an n that works
        int lo = 1, hi = 1e9+5;
        while (lo < hi) {
            int mid = (lo+hi)/2;
            int cur = 1;
            bool over = 0;
            rep(j, 0, i) {
                if ((__int128_t)cur*mid > x) {
                    over = 1;
                    break;
                }
                cur = cur*mid;
            }
            if (over) hi = mid;
            else lo = mid+1;
        }
        int cur = 1;
        int v = lo-1;
        bool ok = 1;
        rep(j, 0, i) {
            if ((__int128_t)cur*v > x) {
                ok = 0; break;
            }
            cur = cur*v;
        }
        // cerr << i << " " << v << " " << ok << " " << cur << endl;
        if (ok && cur == x) {
            // now test if n works
            int cnt = 0;
            for (int j = 1; j*j <= v; j++) {
                if (v%j==0) cnt+=2;
                if (j*j==v) cnt--;
            }
            if (cnt == i) {
                cout << v << endl;
                return 0;
            }
        }
    }
    cout << -1 << endl;
}