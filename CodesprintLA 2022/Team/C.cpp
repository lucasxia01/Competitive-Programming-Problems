#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;
 
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define repb(i, a, b) for(int i = (a); i >= (b); --i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define int ll
#define ln '\n'
//#define pb push_back
#define mp make_pair
#define ff first
#define ss second
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<ll> vll;
typedef unsigned long long ull;
typedef long double ld;
const int S = int(6e3)+10;
const ll INF = ll(1e9)+7;
const ll MOD = 998244353LL;
const int MAG = 15;
const double eps = 1e-8;
const double PI = 3.141592653589793238;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
void print(T &v) {
	//cout << sz(v) << endl;
	trav(x, v)
		cout << x << " ";
	cout << ln;
}


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

typedef Point<double> P;
vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) < eps) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}


int n, ans;
vector <P> p;

int eval(vector <P> &v1, vector <P> &v2) {
    vector<P> c1 = convexHull(v1), c2 = convexHull(v2);
    if(sz(c1) == sz(c2))
        return sz(c1);
    else 
        return 0;
} 


 
signed main()
{
	#ifdef LOCAL
	freopen("stuff.in", "r", stdin);
	//freopen("stuff.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
    //int R = int(1e5);
    cin >> n;
    p.resize(n);
    rep(i, 0, n)
        cin >> p[i].x >> p[i].y;
    
    rep(i, 0, n)
        rep(j, i+1, n) {
            vector <P> v1, v2;
            rep(k, 0, n) {
                if(k != i && k != j) {
                    if(p[i].cross(p[j], p[k]) < 0)
                        v1.push_back(p[k]);
                    else 
                        v2.push_back(p[k]);
                }
            }
            v1.push_back(p[i]);
            v2.push_back(p[j]);
            ans = max(ans, eval(v1, v2));
            v1.pop_back();
            v2.pop_back();

            v2.push_back(p[i]);
            v1.push_back(p[j]);
            ans = max(ans, eval(v1, v2));
            v1.pop_back();
            v2.pop_back();

            v1.push_back(p[i]);
            v1.push_back(p[j]);
            ans = max(ans, eval(v1, v2));
            v1.pop_back();
            v1.pop_back();

            v2.push_back(p[i]);
            v2.push_back(p[j]);
            ans = max(ans, eval(v1, v2));
            v2.pop_back();
            v2.pop_back();
        }

    cout << n - 2*ans << ln;
	
    return 0;
}