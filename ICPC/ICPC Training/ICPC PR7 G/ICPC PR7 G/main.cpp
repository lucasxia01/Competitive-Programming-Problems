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
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define MAX_N 1000011
#define INF (1<<29) + 123
typedef long double ld;
const ld eps = 1e-10;
const ld PI = 4*atan((ld)1);
const char nl = '\n';

using namespace std;

ld m (ld a, ld b, ld c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ld a, b, c;
    cin >> a >> b >> c;
    if (m(a, b, c) * 2 >= a + b + c) {
        cout << -1 << endl;
        return 0;
    }
    ld area = (a*a+b*b+c*c)*sqrtl(3)/4;
    ld s = (a + b + c)/2;
    ld area2 = sqrtl(s * (s - a)) * sqrtl((s - b) * (s - c));
    area += 3 * area2;
    area/=2;
    ld sl = sqrtl(area*4/sqrtl(3));
    if ((a*a+sl*sl-c*c)/(2*a*sl) > 1 || (a*a+sl*sl-b*b)/(2*a*sl) > 1 ||
        (c*c+sl*sl-a*a)/(2*c*sl) > 1 || (c*c+sl*sl-b*b)/(2*c*sl) > 1 ||
        (b*b+sl*sl-a*a)/(2*b*sl) > 1 || (b*b+sl*sl-c*c)/(2*b*sl) > 1) {
        cout << -1 << nl;
        return 0;
    }
    ld angle1 = acosl((a*a+sl*sl-c*c)/(2*a*sl));
    ld angle2 = acosl((a*a+sl*sl-b*b)/(2*a*sl));
    ld angle3 = acosl((c*c+sl*sl-a*a)/(2*c*sl));
    ld angle4 = acosl((c*c+sl*sl-b*b)/(2*c*sl));
    ld angle5 = acosl((b*b+sl*sl-a*a)/(2*b*sl));
    ld angle6 = acosl((b*b+sl*sl-c*c)/(2*b*sl));
    if (abs(PI/3-angle1-angle2) > eps || abs(PI/3-angle3-angle4) > eps || abs(PI/3-angle5-angle6) > eps) {
        cout << -1 << nl;
        return 0;
    }
    ld a1 = acosl((a*a+b*b-sl*sl)/(2*a*b));
    ld a2 = acosl((a*a+c*c-sl*sl)/(2*a*c));
    ld a3 = acosl((c*c+b*b-sl*sl)/(2*c*b));
    if (abs(2*PI-a1-a2-a3) > eps) {
        cout << -1 << nl;
        return 0;
    }
    cout.precision(10);
    cout << fixed << area << endl;
    return 0;
}
