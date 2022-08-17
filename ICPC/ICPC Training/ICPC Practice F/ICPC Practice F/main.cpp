#include <vector>
#include <stack>
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <functional>
#include <set>
#include <cstring>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
#define MAX_N 1000011
#define INF (1<<29) + 123
using namespace std;
ll BIT[MAX_N];

ll query(ll i) {
    int sum = 0;
    i++;
    while (i > 0) {
        sum += BIT[i];
        i -= (i&-i);
    }
    return sum;
}
void update(ll i, ll n, ll v) {
    i++;
    while (i <= n) {
        BIT[i] += v;
        i += (i&-i);
    }
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;
    ll a[n], b[n], c[n];
    rep(i, n) { cin >> a[i]; b[i] = a[i]; }
    sort(b, b + n);
    rep (i, n) a[i] = lower_bound(b, b + n, a[i]) - b + 1;
    for (ll i = n - 1; i >= 0; i--) {
        c[i] = query(a[i] - 1LL);
        //cout << c[i] << " " << i + c[i] - a[i] + 1 << endl;
        update(a[i], n, 1LL);
    }
    ll sum = 0;
    rep(i, n) sum += abs(c[i] * (i + c[i] - a[i] + 1));
    cout << sum << endl;
    return 0;
}
