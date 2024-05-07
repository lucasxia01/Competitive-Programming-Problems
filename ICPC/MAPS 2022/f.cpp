#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point
{
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const
    {
        return P(x + p.x, y + p.y);
    }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x−axis in interval [−pi , pi ]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes d i s t ()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated ’a ’ radians ccw around the origin
    P rotate(double a) const
    {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream &operator<<(ostream &os, P p)
    {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

typedef Point<ll> P;
vector<P> convexHull(vector<P> pts)
{
    if (sz(pts) <= 1)
        return pts;
    sort(all(pts));
    vector<P> h(sz(pts) + 1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(all(pts)))
        for (P p : pts)
        {
            while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0)
                t--;
            h[t++] = p;
        }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

template <class T>
T polygonArea2(vector<Point<T>> &v)
{
    T a = v.back().cross(v[0]);
    rep(i, 0, sz(v) - 1) a += v[i].cross(v[i + 1]);
    return a;
}

int main()
{
    double pi = atan(1) * 4;
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout.precision(12);

    int n, d, g;

    cin >> n >> d >> g;

    vector<P> points;

    for (int i = 0; i < n; ++i)
    {
        int xi, yi;
        cin >> xi >> yi;

        points.push_back(P(xi, yi));
    }

    vector<P> hull = convexHull(points);
    long double area = abs(polygonArea2(hull)) / 2;

    for (int i = 0; i < hull.size(); ++i)
    {
        P pt = hull[i];
        P ptb = hull[(i - 1 + hull.size()) % hull.size()];
        P pta = hull[(i + 1) % hull.size()];

        double edge = sqrt((pta.x - pt.x) * (pta.x - pt.x) + (pta.y - pt.y) * (pta.y - pt.y));

        area += edge * d * g;

        double interior_angle = atan2(ptb.y - pt.y, ptb.x - pt.x) - atan2(pta.y - pt.y, pta.x - pt.x);
        if (interior_angle < 0)
        {
            interior_angle += 2 * pi;
        }

        double angle_of_circle = pi - interior_angle;

        area += angle_of_circle / 2 * (d * g) * (d * g);
    }

    cout << area << endl;
}