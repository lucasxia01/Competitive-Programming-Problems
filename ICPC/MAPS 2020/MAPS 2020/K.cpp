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

const int MAX_N = 100011;
const int MX = 1<<20;
const ll INF = (1LL<<50) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}
int n;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    ld angle() const { return atan2l(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; }
};

template<class P> bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
    // Checks if intersection is single non-endpoint point.
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return {all(s)};
}

int prv(int i) {
    return (i+n-1)%n;
}
int nxt(int i, int k) {
    return (i+k)%n;
}

bool angleInBetween(ld angle1, ld angle2, ld angle3) { // check if angle3 is in between, angles are in between -pi and pi
    if (angle2 < angle1) angle2 += 2*PI;
    if (angle3 < angle1) angle3 += 2*PI;
    return (angle3 > angle1 && angle3 < angle2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    Point<int> p[n];
    F0R(i, n) cin >> p[i].x >> p[i].y;
    ll dp[n][n]; // the answer for the segment [i...j], circular and clockwise
    F0R(i, n) F0R(j, n) dp[i][j] = INF;
    F0R(i, n) dp[i][nxt(i,1)] = dp[i][nxt(i,2)] = 0; // if its 2,3 adjacent points, dp is 0
    int adj[n][n]; // if there exists a line segment between i and j that doesn't intersect
    F0R(i, n) F0R(j, n) {
        if (i == j) adj[i][i] = 0;
        else if (i == prv(j) || j == prv(i)) adj[i][j] = 1;
        else {
            Point<int> v1(p[prv(i)]-p[i]), v2(p[nxt(i,1)]-p[i]), v3(p[j]-p[i]);
            ld a1 = v1.angle(), a2 = v2.angle(), a3 = v3.angle();
            bool ok = angleInBetween(a1, a2, a3);
            F0R(k, n) {
                if (k == i || k == prv(i) || k == j || k == prv(j)) continue;
                if (!ok || sz(segInter(p[i], p[j], p[k], p[nxt(k,1)]))) {
                    ok = false;
                    break;
                }
            }
            adj[i][j] = ok;
        }
    }
    FOR(len, 3, n-1) {
        F0R(i, n) {
            int j = nxt(i, len);
            if (!adj[i][j]) continue;
            for (int k = nxt(i, 1); k != j; k = nxt(k, 1)) {
                if (!adj[i][k] || !adj[j][k]) continue;
                Point<int> a = p[k]-p[i], b = p[k]-p[j];
                ll dist1 = (k == nxt(i,1)) ? 0 : 1LL*a.dist2();
                ll dist2 = (k == prv(j)) ? 0 : 1LL*b.dist2();
                ckmin(dp[i][j], dp[i][k] + dp[k][j] + dist1 + dist2);
            }
            // cout << i << " " << j << " " << dp[i][j] << endl;
        }
    }
    ll ans = dp[0][n-1];
    if (ans != INF) cout << ans << endl;
    else cout << "impossible" << endl;
    return 0;
}
