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

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;
ld EPS = 1e-9;

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


template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (fabsl(d) < EPS) // if parallel
		return {-(fabsl(s1.cross(e1, s2)) < EPS), P(0, 0)};
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}

struct Rect {
    P c[4];
};

Rect rooms[15];
vector<P> v;

int r, l;

int solve(P a, P b) {
    // line through a, b
    if (a == b) return 0;
    vector<pair<P, int> > pts;
    F0R(i, r) {
        F0R(j, 4) {
            pair<int, P> ret = lineInter(a, b, rooms[i].c[j], rooms[i].c[(j+1)%4]);
            if (ret.f == 0) continue;
            else if (ret.f == -1) {
                pts.pb({rooms[i].c[j], i});
                pts.pb({rooms[i].c[(j+1)%4], i});
            } else {
                // check that the point is on the segment
                if (fabsl((ret.s-rooms[i].c[j]).dist() + (ret.s-rooms[i].c[(j+1)%4]).dist() - (rooms[i].c[j]-rooms[i].c[(j+1)%4]).dist()) < EPS) {
                    pts.pb({ret.s, i});
                }
            }
        }
    }
    // sort by coord
    sort(all(pts));
    int ret = 0;
    F0R(i, sz(pts)) {
        set<int> s;
        int j = i;
        while (j < sz(pts) && (pts[j].f-pts[i].f).dist2() <= l*l) {
            s.insert(pts[j].s);
            j++;
        }
        ckmax(ret, int(sz(s)));
    }
    if (ret == 5) cout << a << " " << b << nl;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> r >> l;
    F0R(i, r) {
        P a, b;
        cin >> a.x >> a.y >> b.x >> b.y;
        P c(a.x, b.y);
        P d(b.x, a.y);
        rooms[i].c[0] = a;
        rooms[i].c[1] = c;
        rooms[i].c[2] = b;
        rooms[i].c[3] = d;
        v.pb(a);
        v.pb(b);
        v.pb(c);
        v.pb(d);
    }
    int ans = 1;
    // cout << "hi" << nl;


    F0R(i, sz(v)) {
        F0R(j, i) {
            // we have two corners and now we can check intersections with all segments
            // cout << i << " " << j << nl;
            ckmax(ans, solve(v[i], v[j]));
        }
        F0R(j, 100) F0R(k, 100) {
            P temp(j, k);
            ckmax(ans, solve(v[i], temp));
        }
    }
    // cout << "hi" << nl;

    cout << ans << nl;
    return 0;
}
