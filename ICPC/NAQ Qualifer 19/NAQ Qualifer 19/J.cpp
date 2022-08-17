#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cmath>
#define ll long long
#define ld long double

#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define F0Rd(i, n) for (int i = n-1; i >= 0; i--)

using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n];
    ld best = 0, temp;
    ll sum = 0;
    ll count = 0;
    F0R(i, n) {
        cin >> a[i];
        sum += a[i];
        count++;
        temp = (ld) sum/count;
        if (temp > best) best = temp;
    }
    ld best1 = 0;
    sum = 0;
    count = 0;
    F0Rd(i, n) {
        sum += a[i];
        count++;
        temp = (ld) sum/count;
        if (temp > best1) best1 = temp;
    }
    cout.precision(15);
    if (best > best1) cout << best << endl;
    else cout << best1 << endl;
    return 0;
}
