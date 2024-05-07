#include <bits/stdc++.h>

#define int long long
#define pi pair<int, int>
#define vi vector<int>
#define vpi vector<pi>
#define rep(i, a, b) for(int i = a; i < (b); i++)
using namespace std;

signed main() {
    int t; cin >> t;
    while (t--) {
        int n, d; cin >> n >> d;
        int cur = 1;
        rep(i, 0, 63) {
            if (cur >= n) {
                cout << i << '\n';
                break;
            }
            if ((__int128_t)cur * (d+1) > (int)1e18) {
                cur = (int)1e18;
            } else cur = cur*(d+1);
        }
    }
}