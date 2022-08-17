#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define F0R(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define FORd(i,a,b) for (int i = (b); i >= (a); i--)
#define trav(a, x) for (auto& a : x)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MX = 1e7+5;
const ld eps = 1e-5;

struct Point {
    ld x, y;
};

// angle between vectors (a-c) and (b-c)
ld angle(Point a, Point b, Point c) {
    a.x -= c.x; a.y -= c.y;
    b.x -= c.x; b.y -= c.y;
    // dot product
    return acosl((a.x*b.x+a.y*b.y)/(sqrtl(a.x*a.x+a.y*a.y)*sqrtl(b.x*b.x+b.y*b.y)));
}

// check angle*n close enough to integer
bool check(ld angle, int n) {
    return (fabsl(angle*n - round(angle*n)) < eps);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Point p[3];
    for (;;) {
        F0R(i, 3) if (scanf("%Lf %Lf", &p[i].x, &p[i].y) != 2) return 0;
        // calculate the 2 angles between two pairs of points
        ld a1 = angle(p[0], p[1], p[2])/PI;
        ld a2 = angle(p[1], p[2], p[0])/PI;
        for (int n = 3; n <= 1000; n++) { // n is number of sides
            // we want to check if the angle theta * n is close enough to some integer k
            if (check(a1, n) && check(a2, n)) {
                cout << n << nl;
                break;
            }
        }
        
    }
    return 0;
}
