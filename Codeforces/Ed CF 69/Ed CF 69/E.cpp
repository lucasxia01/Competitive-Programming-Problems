#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>
#define MOD 1000000007

using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    cin >> n;
    pair<long long, long long> a[n];
    long long latestStart = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        latestStart = max(latestStart, a[i].second);
    }
    sort(a, a + n);
    unordered_map<long long, long long> minSpaces; // first is ending position, second is min space
    minSpaces.insert(make_pair(0, 0));
    vector<long long> ends;
    ends.push_back(0);
    long long minSpace = 1<<30;
    for (int i = 0; i < n; i++) {
        long long prevEnd = ends[(upper_bound(ends.begin(), ends.end(), a[i].second) - ends.begin()) - 1];
        //cout << a[i].second << " " << prevEnd << " " << minSpaces[prevEnd] << endl;
        if (minSpace > minSpaces[prevEnd] + a[i].second - prevEnd) {
            minSpace = minSpaces[prevEnd] + a[i].second - prevEnd;
        }
        if (i == n-1 || a[i].first != a[i+1].first) {
            ends.push_back(a[i].first);
            minSpaces.insert(make_pair(a[i].first, minSpace));
            minSpace = 1<<30;
        }
    }
    unordered_map<long long, long long> ways; // first is ending position, second is ways
    ways.insert(make_pair(0, 1));
    long long count = 0;
    for (int i = 0; i < n; i++) {
        long long idx = (upper_bound(ends.begin(), ends.end(), a[i].second) - ends.begin()) - 1;
        long long prevEnd = ends[idx];
        //cout << a[i].second << " " << prevEnd << " " << minSpaces[prevEnd] << endl;
        while (minSpaces[prevEnd] + a[i].second - prevEnd == minSpaces[a[i].first]) {
            count = (count + ways[prevEnd]) % MOD;
            idx--;
            if (idx < 0) break;
            prevEnd = ends[idx];
        }
        if (i == n-1 || a[i].first != a[i+1].first) {
            ways.insert(make_pair(a[i].first, count));
            count = 0;
        }
    }
    long long ans = 0;
    long long overallMin = 1<<30;
    for (auto it: minSpaces) {
        if (it.first > latestStart) {
            overallMin = min(overallMin, it.second);
        }
    }
    for (auto it: ways) {
        //cout << it.first << " " << it.second << " " << minSpaces[it.first] << endl;
        if (it.first > latestStart && minSpaces[it.first] == overallMin) {
            ans = (ans + it.second) % MOD;
        }
    }
    cout << ans << endl;
    return 0;
}
