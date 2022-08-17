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
#include <climits>

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
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);
const ld eps = 1e-5;

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;


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
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<ld> P;

template<class P> vector<P> seglineInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b);
    // Checks if intersection is single non-endpoint point.
    if (sgn(oa) * sgn(ob) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    return {all(s)};
}

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0) // if parallel
        return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}

template<class P>
pair<int, P> raylineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0) // if parallel
        return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
//    dbg(p, q, d, s1, e1, s2, e2);
    if (q/d <= eps) return {0, P(0, 0)};
    return {1, (s1 * p + e1 * q) / d};
}

ld newDist(P a, P b, P c, P d) {
    pair<int, P> p = raylineInter(a, b, c, d);
    if (p.f != 1) return INF;
    P e = p.s;
    ld ret = min((e-a).dist(), (e-b).dist());
//    dbg(a, b, c, d, ret);
    return ret;
}

int n, m;
int nxt(int i) {
    return (i+1)%m;
}
int prv(int i) {
    return (i+m-1)%m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    P a[n]; F0R(i, n) cin >> a[i].x >> a[i].y;
    cin >> m;
    P b[m]; F0R(i, m) cin >> b[i].x >> b[i].y;
    ld d[m][2]; F0R(i, m) d[i][0] = d[i][1] = -1;
    ld ans = 0;
    F0R(j, m) ans += (b[j]-b[nxt(j)]).dist();
    F0R(j, m) {
        int cnt = 0;
        F0R(i, n) {
//            dbg(a[i], a[(i+1)%n], b[j], b[nxt(j)]);
            vector<P> v = seglineInter(a[i], a[(i+1)%n], b[j], b[nxt(j)]);
//            if (sz(v)) dbg(v[0]);
            if (sz(v) == 0) continue;
            assert(sz(v) == 1);
            cnt++;
            P p = v[0];
            ld d1 = (p-b[j]).dist();
            ld d2 = (p-b[nxt(j)]).dist();
            if (d1 < d2) d[j][0] = d1;
            else d[j][1] = d2;
        }
//        dbg(cnt, b[j], b[nxt(j)])
        assert(cnt == 2);
    }
    ld dp[m][m]; F0R(i, m) F0R(j, m) dp[i][j] = INF;
    F0R(i, m) dp[i][i] = 0;
    FOR(len, 1, m-1) {
        F0R(i, m) {
            int j = (i+len)%m;
            if (len == 1) dp[i][j] = 0;
            else {
                // middle segment
                F0R(jj, len) {
                    int k = (i+jj)%m;
                    ld d1 = min(d[k][0], newDist(b[nxt(k)], b[k], b[prv(i)], b[i]));
                    ld d2 = min(d[k][1], newDist(b[k], b[nxt(k)], b[j], b[nxt(j)]));
                    ckmin(dp[i][j], d1+d2 + dp[i][k]+dp[nxt(k)][j]);
                }
            }
//            dbg(i, j, dp[i][j]);
        }
    }
    ld rest = INF;
    F0R(i, m) {
        // try i, i+1 as first one
//        dbg(b[i], b[nxt(i)], d[i][0], d[i][1], dp[nxt(i)][i]);
        ckmin(rest, d[i][0]+d[i][1]+dp[nxt(i)][i]);
    }
    cout.precision(10);
//    dbg(ans, rest);
    cout << fixed << ans+rest << nl;
    return 0;
}
