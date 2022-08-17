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

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    if (a + b + c + d == 0) {
        cout << "0" << endl;
        return 0;
    }
    bool pos = true;
    for (ll i = 1; a > 0;i++) {
        if (i * (i + 1)/2 == a) {
            a = i + 1;
            break;
        }else if (i * (i + 1)/2 > a) {
            pos = false;
            break;
        }
    }
    //cout << pos << endl;
    for (ll i = 1; d > 0 ;i++) {
        if (i * (i + 1)/2 == d) {
            d = i + 1;
            break;
        } else if (i * (i + 1)/2 > d) {
            pos = false;
            break;
        }
    }
    //cout << pos << endl;
    if ((b + c) != a * d) {
        if (a != 0 && d != 0) pos = false;
        else {
            //cout << "hi" << endl;
            if (a == 0 && d == 0 && b + c == 1) {
                a = 1;
                d = 1;
            } else if (a == 0 && b + c == d) {
                a = 1;
            } else if (d == 0 && b + c == a) {
                d = 1;
            } else {
                pos = false;
            }
        }
    }
    string ans = "";
    //cout << a << " " << d << endl;
    if (pos) {
        ll id = -2;
        ll num = -1;;
        if (d != 0) {
            id = b/d;
            num = d - (b % d);
        }
        rep(i, a)  {
            if (i == id) rep(i, num) ans += "1";
            if (i == id + 1) rep(i, d - num) ans += "1";
            ans += "0";
        }
        if (a == id) rep(i, num) ans += "1";
        if (a == id + 1) rep(i, d - num) ans += "1";
        cout << ans << endl;
    } else cout << "impossible" << endl;
    return 0;
}

