#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cmath>

#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define ll long long

using namespace std;

ll sqrt1(ll x) {
    ll lo = 0, hi = 1LL<<31, mid = (lo+hi)/2;
    while (lo <= hi) {
        mid = (lo + hi)/2;
        if (mid*mid <= x && (mid+1)*(mid+1)>x) break;
        if (mid*mid > x) {
            hi = mid-1;
        } else {
            lo = mid+1;
        }
        cout << mid << endl;
    }
    ll rem = x - mid*mid;
    cout << mid;
    
    return rem;
}
int main() {
    ll n, w, g, h, r, a, b;
    //cout << sqrt1(10000000000000) << endl;
    long double minAns, maxAns, x, y;
    cin >> n;
    cout.precision(15);
    F0R(i, n) {
        cin >> w >> g >> h >> r;
        a = max(g, h);
        b = min(g, h);
        minAns = sqrt((a-b)*(a-b) + w*w);
        if (g+h == 2*r) x = 0;
        else x = (long double) w*(g-r)/(g+h-2*r);
        y = w-x;
        maxAns = sqrt(x*x+(g-r)*(g-r)) + sqrt(y*y+(h-r)*(h-r));
        cout << minAns << " " << maxAns << endl;
    }
    return 0;
}
