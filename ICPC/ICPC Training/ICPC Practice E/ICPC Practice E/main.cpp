#include <iostream>
#include <set>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <string>
#include <algorithm>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
using namespace std;

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll a, b, c, m;
    string x;
    cin >> a >> b >> c >> m;
    pair<ll, ll> ms[m];
    rep(i, m) {
        cin >> ms[i].first >> x;
        x == "USB" ? ms[i].second = 0 : ms[i].second = 1;
    }
    ll cost = 0;
    ll count = 0;
    sort(ms, ms + m);
    rep (i, m) {
        if (ms[i].second == 0) {
            if (a > 0) {
                cost += ms[i].first;
                a--;
                count++;
            } else if (c > 0) {
                cost += ms[i].first;
                c--;
                count++;
            }
        } else {
            if (b > 0) {
                cost += ms[i].first;
                b--;
                count++;
            } else if (c > 0) {
                cost += ms[i].first;
                c--;
                count++;
            }
        }
    }
    cout << count << " " << cost << endl;
    return 0;
}
