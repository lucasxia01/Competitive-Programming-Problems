#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <set>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

#define F0R(i, n) for(int i = 0; i < n; i++)
#define FOR(i, s, e) for (int i = s; i < e; i++)

int comparePoints(pair<long long, long long> a, pair<long long, long long> b) {
    if (a.second != b.second) return a.second > b.second;
    return a.first < b.first;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    pair<long long, long long> points[n];
    int x, y;
    F0R(i, n) {
        cin >> x >> y;
        points[i] = make_pair(x, y);
    }
    sort(points, points+n, comparePoints);
    ordered_set xValues;
    long long size = 0, ans = 0;
    long long size1 = 0, overCount = 0;
    for (int i = 0; i < n; i++) {
        //cout << points[i].first << ", " << points[i].second << endl;
        xValues.insert(points[i].first);
        if (i == 0 || points[i].second != points[i-1].second) {
            size1 = xValues.order_of_key(points[i].first);
            overCount+= (size1+1)*size1/2;
        }
        if (i != 0 && points[i].second == points[i-1].second) {
            size1 = xValues.order_of_key(points[i].first) - xValues.order_of_key(points[i - 1].first) - 1;
            overCount+= (size1+1)*size1/2;
            //cout << "Overcount: " << xValues.order_of_key(points[i].first) << " " << xValues.order_of_key(points[i - 1].first) << endl;
        }
        if (i == n - 1 || points[i].second != points[i+1].second) {
            size = xValues.size();
            //cout << size << endl;
            ans += (size+1)*size/2;
            size1 = size - 1 - xValues.order_of_key(points[i].first);
            overCount+= (size1+1)*size1/2;
            //cout << "Overcount: " << overCount << endl;
            ans -= overCount;
            overCount = 0;
        }
    }
    cout << ans << endl;
    return 0;
}
