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

#define rep(i,n) for (ll i = 0; i < n; i++)
#define ll long long
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define MAX_N 1000011
#define INF (1<<29) + 123

using namespace std;

ll w[101];
ll p[101];
ll l, m;
void check(ll i, ll c, ll t, ll s) {
    //double weight = (c * t)/(t + s);
    if ((c * t) * 10080 >=  l * (t + s)) w[i] = 1;
}
ll ai (string s) {
    ll l = (ll) s.length();
    ll power = 1;
    ll ans = 0;
    rep(i, l) {
        ans += power * (s[l - i - 1] - '0');
        power *= 10;
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll price, cutrate, time, sleep;
    cin >> l >> m;
    string n[101] = {};
    string s;
   
    ll mi = 100011;
    getline(cin, s);
    rep(i, m) {
        getline(cin, s);
        ll j = 0;
        ll prev = 0;
        while (s[j] != ',') {
            j++;
        }
        n[i] = s.substr(prev, j);
        prev = j + 1;
        j++;
        while (s[j] != ',') {
            j++;
        }
        price = ai(s.substr(prev, j - prev));
        p[i] = price;
        prev = j + 1;
        j++;
        while (s[j] != ',') {
            j++;
        }
        cutrate = ai(s.substr(prev, j - prev));
        prev = j + 1;
        j++;
        while (s[j] != ',') {
            j++;
        }
        time = ai(s.substr(prev, j - prev));
        prev = j + 1;
        j++;
        while (j < s.length()) {
            j++;
        }
       sleep = ai(s.substr(prev, j - prev));
        //cout << n[i] << " " << price << " " << cutrate << " " << time << " " << sleep << endl;
        check(i, cutrate, time, sleep);
        if (w[i]) mi = min(mi, price);
    }
    rep(i, m) {
        if (p[i] == mi && w[i]) cout << n[i] << endl;
    }
    if (mi == 100011) cout << "no such mower" << endl;
    return 0;
}
