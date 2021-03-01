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
#define ROF(i,a,b) for(int i = b-1; i >= a; i--)
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
const ll INF = (1LL<<50) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

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
const int MX = 1e5+5;

double expected_abs_diff_trap(double x1, double x2, double h1, double h2) {
    double temp = min(h1, h2), temp2 = max(h1, h2);
    h1 = temp; h2 = temp2;
    // symbolic integration
    double area = ((h1 + h2)/2.) * (x2-x1);
    double a = (h2-h1)/((x2-x1)*area);
    double b = ((x1+1)*h1 - x1*h2)/((x2-x1)*area);
    // dbg("a,b",a,b);
    vector<vector<double>> poly(3, vector<double>(3));
    poly[0][1] = -1;
    poly[1][0] = 1;
    // dbg("poly",poly);
    ROF(i,0,3) ROF(j,0,3) {
        poly[i][j] = b * poly[i][j];
        if (i > 0) poly[i][j] += a * poly[i-1][j];
    }
    // dbg("poly",poly);
    ROF(i,0,3) ROF(j,0,3) {
        poly[i][j] = b * poly[i][j];
        if (j > 0) poly[i][j] += a * poly[i][j-1];
    }
    // dbg("poly",poly);
    vector<double> next_poly(5);
    FOR(i,0,2) FOR(j,0,2) {
        next_poly[i] -= poly[i][j] * pow(x1,j+1) / ((double)(j+1));
        next_poly[i+j+1] += poly[i][j] / ((double)(j+1));
    }
    // dbg("next_poly",next_poly)
    double ans = 0;
    FOR(i,0,4) ans += next_poly[i] * (pow(x2,i+1) - pow(x1,i+1)) / ((double)(i+1));
    return 2*ans;
}
int n;
P pts[MX]; 
ld solve() {
    ld ans = 0;
    int idx = 0; int X = pts[0].x, Y = pts[0].y;
    F0R(i, n) {
        if (pts[i].x < X) {
            idx = i;
            X = pts[i].x; Y = pts[i].y;
        } else if (pts[i].x == X && pts[i].y > Y) {
            idx = i;
            X = pts[i].x; Y = pts[i].y;
        }
    }
    vector<P> u, l; 
    bool ok = 1;
    F0R(i, n) {
        if (ok) u.pb(pts[(idx+i)%n]);
        else l.pb(pts[(idx+i)%n]);
        if (pts[(idx+i)%n].x >= pts[(idx+i+1)%n].x) ok = 0;
    }
    sort(all(u));
    sort(all(l));
    l.insert(l.begin(), u[0]); l.pb(u.back());
    // trav(uu, u) dbg(uu);
    // trav(ll, l) dbg(ll);


    int N = sz(u), M = sz(l);
    int i = 0, j = 0;
    vector<pair<ld, ld> > heights; // x coord, length of vert line
    while (i < N && j < M) {
        // dbg(u[i], l[j]);
        if (u[i].x == l[j].x) {
            heights.pb({u[i].x, u[i].y-l[j].y});
            i++;
            j++;
        } else if (u[i].x < l[j].x) {
            // draw line down from u[i] intersecting l[j-1], l[j]
            P t(u[i].x, -INF);
            vector<P> temp = segInter(u[i], t, l[j-1], l[j]);
            assert(sz(temp) == 1);
            P pt = temp[0];
            heights.pb({u[i].x, u[i].y-pt.y});
            i++;
        } else {
            // draw line up from l[j] intersecting u[i-1], u[i]
            P t(l[j].x, INF);
            vector<P> temp = segInter(l[j], t, u[i-1], u[i]);
            assert(sz(temp) == 1);
            P pt = temp[0];
            heights.pb({l[j].x, pt.y-l[j].y});
            j++;
        }
    }
    heights.pb({u.back().x, 0});
    // trav(h, heights) dbg(h.f, h.s);
    int H = sz(heights);
    vector<pair<ld, ld> > traps; // center of mass and area
    F0R(i, H-1) {
        ld dx = heights[i+1].f-heights[i].f;
        if (dx == 0) traps.pb({heights[i].f, 0});
        else {
            ld center = heights[i].f + (heights[i].s/3 + heights[i+1].s/3*2)/(heights[i].s+heights[i+1].s) * dx;
            traps.pb({center, (heights[i].s+heights[i+1].s)/2 * dx});
            // dbg("CENTERS", center)
        }
    }
    // trav(t, traps) dbg(t.f, t.s);
    int T = sz(traps);
    ld total = 0, totalA = 0;
    F0R(i, T) {
        total += traps[i].f*traps[i].s;
        totalA += traps[i].s;
    }
    ld cur = total, curA = totalA;
    F0R(i, T) {
        cur -= traps[i].f*traps[i].s;
        curA -= traps[i].s;
        if (curA == 0) continue;
        // dbg(traps[i].f, traps[i].s, cur, curA);
        ans += (ld)2*fabsl(traps[i].f - cur/curA) * curA/totalA * traps[i].s/totalA;
    }
    // dbg("HI", ans)
    // dbg(T, H, totalA);
    F0R(i, T) {
        if (heights[i].f == heights[i+1].f) continue;
        // dbg(heights[i].f, heights[i+1].f, heights[i].s, heights[i+1].s);
        ld dx = heights[i+1].f - heights[i].f;
        ans += expected_abs_diff_trap(0, 1, heights[i].s/dx, heights[i+1].s/dx) * traps[i].s/totalA * traps[i].s/totalA * dx;
    }
    // dbg("HI2", ans);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    F0R(i, n) cin >> pts[i].x >> pts[i].y;
    ld ans = 0;
    ans += solve();
    dbg(ans);
    F0R(i, n) swap(pts[i].x, pts[i].y);
    reverse(pts, pts+n);
    ans += solve();
    cout.precision(10);
    cout << fixed << ans << nl;
    return 0;
}