//
//  main.cpp
//  Ed CF 50 E
//
//  Created by Lucas Xia on 9/9/18.
//  Copyright © 2018 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <set>
#include <utility>
#include <cmath>
#include <cstdlib>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
using namespace std;

ll p[1012][1012];
ll sum = 0, total = 0;

void solve(ll i, ll j, ll x1, ll y1, ll x2, ll y2, ll a1, ll b1, ll a2, ll b2) {
    ll d4 = a1 - a2;
    ll d3 = b1 - b2;
    ll d2 = x1 - x2;
    ll d1 = y1 - y2;
    ll x = d2 * d4 * y1 + d2 * d3 * a1 - d1 * d4 * x1 - d2 * d4 * b1;
    ll y = d2 * d3 * y1 + d1 * d3 * a1 - d1 * d3 * x1 - d1 * d4 * b1;
    ll d = d2 * d3 - d1 * d4;
    //cout << "hi " << i << " " << j << " " << " " << x << " "  << y << " " << d << endl;
    if (d != 0LL && x % d == 0LL && y % d == 0LL) {
        x = x / d;
        y = y / d;
        if (x >= -1000000 && x <= 1000000 && y >= -1000000 && y <= 1000000 && (x - x1) * (x - x2) <= 0LL && (x - a1) * (x - a2) <= 0LL && (y - y1) * (y - y2) <= 0LL && (y - b1) * (y - b2) <= 0LL) {
            p[i][j] = (x + 1000000LL) * 2000001LL + (y + 1000000LL);
        } else p[i][j] = -1;
        
    } else p[i][j] = -1;
}
ll gcd(ll a, ll b) {
    if (a == 0 || a == b) return b;
    else if (b == 0) return a;
    return gcd(max(a, b) % min(a, b), min(a, b));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    ll a[n][4];
    
    rep(i, n) rep(j, 4) cin >> a[i][j];
    rep(i, n) {
        sum += gcd(abs(a[i][0] - a[i][2]), abs(a[i][1] - a[i][3])) + 1;
    }
    rep(i, n) rep(j, n) if (i != j) solve(i, j, a[i][0], a[i][1], a[i][2], a[i][3], a[j][0], a[j][1], a[j][2], a[j][3]); else p[i][j] = -1;
    set<ll> s;
    set<ll> s1;
    rep(i, n) {
        rep(j, n) {
            if (p[i][j] != -1) {
                s.insert(p[i][j]);
                s1.insert(p[i][j]);
            }
        }
        total += s1.size();
        s1.clear();
    }
    cout << sum - total + s.size() << endl;
    return 0;
}
