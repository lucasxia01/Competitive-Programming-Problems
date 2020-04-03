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

const int MX = 1e5+5;

struct Line { // ax + by + c = 0;
    ld a, b, c;
    int x1, y1, x2, y2;
};

ld igs[505][505];

bool dist(int x, int y, ld r, Line l) { // returns true if the line intersects the circle
    if (x < l.x1 || x > l.x2 || y < l.y1 || y > l.y2) return false;
    ld dist = abs(l.a*x + l.b*y + l.c)/sqrt(l.a*l.a+l.b*l.b);
    return (dist < r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q, x1, y1, x2, y2;
    ld r;
    cin >> n;
    F0R(i, n) {
        cin >> x1 >> y1 >> r;
        igs[x1][y1] = r;
    }
    cin >> q;
    F0R(i, q) {
        Line l;
        cin >> x1 >> y1 >> x2 >> y2;
        l.x1=min(x1, x2); l.y1=min(y1, y2); l.x2=max(x1, x2); l.y2=max(y1, y2);
        l.a = -(y2-y1);
        l.b = (x2-x1);
        l.c = -(l.a*x1 + l.b*y1);
        int ans = 0;
        if (x1 == x2) { // vertical line case
            FOR(y, min(y1, y2), max(y1, y2)) {
                if (igs[x1][y]) ans++;
            }
        } else if (y1 == y2) { // horizontal line case
            FOR(x, min(x1, x2), max(x1, x2)) {
                if (igs[x][y1]) ans++;
            }
        } else {
            if (abs(l.b) >= abs(l.a)) { // if line is more flat, use y
                FOR(x, min(x1, x2), max(x1, x2)) {
                    ld curY = (-l.a*x-l.c)/l.b;
                    ld dy = sqrt(l.a*l.a+l.b*l.b)/abs(l.b); // generate all the points close enough to the line
                    int lb = ceil(curY-dy) > 1 ? ceil(curY-dy) : 1;
                    int ub = floor(curY+dy) < 500 ? floor(curY+dy) : 500;
                    FOR(y, lb, ub) {
                        if (igs[x][y] > 0 && dist(x, y, igs[x][y], l)) ans++;
                    }
                }
            } else { // if line is more steep, use x
                FOR(y, min(y1, y2), max(y1, y2)) {
                    ld curX = (-l.b*y-l.c)/l.a;
                    ld dx = sqrt(l.a*l.a+l.b*l.b)/abs(l.a);
                    int lb = ceil(curX-dx) > 1 ? ceil(curX-dx) : 1;
                    int ub = floor(curX+dx) < 500 ? floor(curX+dx) : 500;
                    FOR(x, lb, ub) {
                        if (igs[x][y] > 0 && dist(x, y, igs[x][y], l)) {
                            ans++;
                        }
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
