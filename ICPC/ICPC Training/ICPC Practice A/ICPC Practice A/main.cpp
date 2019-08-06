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
int a[100011];

int bS(int size, int key) {
    int lo = 0, hi = size - 1, mid = mid = (lo + hi)/2;
    
    return mid;
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n;
    rep(i, n) {
        cin >> a[i];
    }
    cin >> q;
    sort(a, a + n);
    pair<int , int> b[100011];
    rep(i, q) {
        cin >> b[i].first;
        b[i].second = i;
    }
    sort(b, b + q);
    int pos = 0;
    int ans[100011];
    rep(i, q) {
        while (a[pos] <= b[i].first && pos < n) {
            pos++;
        }
        pos--;
        ans[b[i].second] = pos + 1;
        //cout << b[i].first << " " << pos << endl;
    }
    rep (i, q) {
        cout << ans[i] << endl;
    }
    return 0;
}
