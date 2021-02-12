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
#include <iomanip>
#include <ctime>

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

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

template<class T> struct Point3D {
    typedef Point3D P;
    typedef const P& R;
    T x, y, z;
    explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
    bool operator<(R p) const {
        return tie(x, y, z) < tie(p.x, p.y, p.z); }
    bool operator==(R p) const {
        return tie(x, y, z) == tie(p.x, p.y, p.z); }
    P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
    P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
    P operator*(T d) const { return P(x*d, y*d, z*d); }
    P operator/(T d) const { return P(x/d, y/d, z/d); }
    T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
    P cross(R p) const {
        return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
    }
    T dist2() const { return x*x + y*y + z*z; }
    double dist() const { return sqrt((double)dist2()); }
    //Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
    double phi() const { return atan2(y, x); }
    //Zenith angle (latitude) to the z-axis in interval [0, pi]
    double theta() const { return atan2(sqrt(x*x+y*y),z); }
    P unit() const { return *this/(T)dist(); } //makes dist()=1
    //returns unit vector normal to *this and p
    P normal(P p) const { return cross(p).unit(); }
    //returns point rotated 'angle' radians ccw around axis
    P rotate(double angle, P axis) const {
        double s = sin(angle), c = cos(angle); P u = axis.unit();
        return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
    }
};

typedef Point3D<ld> P;
const ld eps = 1e-8;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        P t1[3], t2[3];
        F0R(i, 3) cin >> t1[i].x >> t1[i].y >> t1[i].z;
        F0R(i, 3) cin >> t2[i].x >> t2[i].y >> t2[i].z;
        P normal = (t1[0]-t1[1]).cross(t1[0]-t1[2]);
        ld x = normal.dot(t1[0]);
        vector<ld> v;
        F0R(i, 3) v.pb(normal.dot(t2[i])-x);
        if (*min_element(all(v)) >= -eps || *max_element(all(v)) <= eps) {
            cout << "NO" << nl;
            continue;
        }
        set<P> pts;
        F0R(i, 3) { // testing t2[i] and t2[i+1]
            int ii = (i+1)%3;
            P p1 = t2[i], p2 = t2[ii];
            if (fabsl(v[i]) <= eps) continue;
            if (v[i]*v[ii] <= 0) { // diff sides
                if (fabsl((p2-p1).dot(normal)) <= eps) continue;
                ld t = (x-p1.dot(normal))/((p2-p1).dot(normal));
                P p3 = p1+(p2-p1)*t;
                assert(fabsl(normal.dot(p3)-x) <= eps);
                // check if the point is inside sthe triangle
//                dbg(i, p3.x, p3.y, p3.z);
                vector<ld> crosses;
                F0R(j, 3) {
                    int jj = (j+1)%3;
                    crosses.pb((p3-t1[j]).cross(p3-t1[jj]).dot(normal));
                }
                if (*min_element(all(crosses)) >= -eps || *max_element(all(crosses)) <= eps) {
//                    dbg(i, p3.x, p3.y, p3.z);
                    pts.insert(p3);
                }
            }
        }
        cout << (sz(pts)==1?"YES":"NO") << nl;
    }
    
    return 0;
}
