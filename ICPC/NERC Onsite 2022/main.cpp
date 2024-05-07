#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = a; i < b; i++)
#define pi pair<int, int>
#define nl '\n'
#define vi vector<int>
#define vpi vector<pi>
#define pb push_back
using namespace std;

int main() {
    int n, k; cin >> n >> k;
    if (n == 1) {
        cout << "YES" << nl;
        cout << 0 << nl;
        return 0;
    } else if (k == 1 && n == 2) {
        cout << "YES" << nl;
        cout << 1 << nl;
        cout << "1 2" << nl;
        return 0;
    } else if (k == 1 && n > 2) {
        cout << "YES" << nl;
        cout << n << nl;
        rep(i, 0, n) {
            cout << i+1 << " " << (i+1)%n + 1 << nl;
        }
        return 0;
    } else if (k == n) {
        cout << "NO" << nl;
        return 0;
    }
    cout << "YES" << nl;
    vi cur;
    vpi ans;
    ans.pb({1, 2});
    ans.pb({2, 3});
    cur.pb(1); cur.pb(2);
    rep(i, 4, k+2) {
        for (auto a: cur) {
            ans.pb({i, a});
        }
        if (i%2) cur.pb(i);
    }
    rep(i, 0, n-1-k) {
        ans.pb({i+k+2, 2});
    }

    // int cnt[n+1]; memset(cnt, 0, sizeof cnt);
    // for(auto a: ans) {
    //     cnt[a.first]++;
    //     cnt[a.second]++;
    // }
    // set<int> d;
    // rep(i, 1, n+1) {
    //     d.insert(cnt[i]);
    // }
    // assert(d.size() == k);

    cout << ans.size() << nl;
    for (auto a: ans) cout << a.first << " " << a.second << nl;

}