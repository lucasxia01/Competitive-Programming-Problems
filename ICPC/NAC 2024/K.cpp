#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(v) v.begin(), v.end()
#define sz(v) (int)v.size()
#define sq(a) ((a)*(a))

#define MOO(i,a,b) for (int i=a; i<b; i++)
#define M00(i,a) for (int i=0; i<a; i++)
#define MOOd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define M00d(i,a) for (int i = (a)-1; i >= 0; i--)

#define per(i,a,b) for (int i = (b)-1; i >= a; i--)
#define rep(i,a,b) for (int i=a; i<b; i++)

#define FOR(i,a,b) for (int i=a; i<b; i++)
#define F0R(i,a) for (int i=0; i<a; i++)
#define ROF(i,a,b) for (int i = (b)-1; i >= a; i--)
#define R0F(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);
#define finish(x) return cout << x << endl, 0;
#define dbg(x) cerr << ">>> " << #x << " = " << x << endl;
#define _ << " _ " <<

#define int long long

template<class T> bool ckmin(T&a, T&b) { bool B = a > b; a = min(a,b); return B; }
template<class T> bool ckmax(T&a, T&b) { bool B = a < b; a = max(a,b); return B; }

typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ld,ld> pld;
typedef complex<ld> cd;

typedef vector<int> vi;
typedef vector<ld> vld;
typedef vector<vector<int>> vvi;

const ld PI = acos(-1.0);
const ld EPS = 1e-7;
const int MOD = 1e9+7;

bool pt_comparison(array<int, 4> &a, array<int, 4> &b) {
	if(b[0] * a[1] > a[0] * b[1]) return true;
	if(b[0] * a[1] < a[0] * b[1]) return false;
	return b[0] > a[0];
}

bool event_comparison(array<int, 4> &a, array<int, 4> &b) {
	if(b[0] * a[1] != a[0] * b[1])
		return b[0] * a[1] > a[0] * b[1];
	return b[2] > a[2];
}

int32_t main() { FAST
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	int n;
	int w;
	cin >> n >> w;
	vector<pair<pi, int>> pts; // just the points with start and end marked
	vector<pi> inters; // segments of ys projected onto the wall
	vector<array<int, 4>> pts_sorted; // points sorted by y and then x with index
	int miny = 10000000; 
	int maxy = -miny;
	M00(i, n) {
		int x, y1, y2;
		cin >> x >> y1 >> y2;
		pts.pb(mp(mp(x,y1), 0));
		pts.pb(mp(mp(x,y2), 1));

		array<int, 4> a = {y1, x, i * 2};
		array<int, 4> b = {y2, x, i * 2 + 1};
		pts_sorted.pb(a);
		pts_sorted.pb(b);

		inters.pb(mp(y1, y2));

		miny = min(miny, y1);
		maxy = max(maxy, y2);
	}
	sort(all(inters)); // sorted by y1
	int reach = inters[0].s;
	for(auto p : inters) {
		if(reach >= p.f) {
			reach = max(p.s, reach);
		}
	}
	bool canInf = reach == maxy;



	// for(auto pt : pts) {
	// 	dbg(pt.f.f _ pt.f.s _ pt.s);
	// }
	sort(pts_sorted.begin(), pts_sorted.end(), pt_comparison);
	reverse(all(pts_sorted));
	// for(auto pt : pts_sorted) {
	// 	dbg(pt[0] _ pt[1] _ pt[2]);
	// }

	vi pos(2 * n); // pos[0] = index to pts sorted array that is highest y
	vi rpos(2 * n); // reverse of pos

	M00(i, 2 * n) {
		pos[i] = pts_sorted[i][2];
		rpos[pts_sorted[i][2]] = i;
	}
	vi covers(2 * n - 1);
	M00(i, 2 * n) {
		if(pos[i] % 2 == 1) {
			int ii = i;
			while(pos[ii] != pos[i] - 1) {
				covers[ii] += 1;
				ii += 1;
			}
		}
	}
	// for(auto x : covers) dbg(x);
	int covers_zero = 0;
	M00(i, 2 * n - 1) if(covers[i] == 0) covers_zero++;
	
	vector<array<int, 4>> events;
	M00(i, pts.size()) {
		MOO(j, i+1, pts.size()) {
			auto [x1, y1] =  pts[i].f;
			auto [x2, y2] =  pts[j].f;
			if(x1 == x2) continue;
			if(y1 == y2) continue;
			int y_delta = y2 - y1;
			int x_delta = x2 - x1;
			pi intersection = mp(x1 * y_delta - y1 * x_delta, y_delta);
			if(y_delta < 0) {
				intersection = mp(-intersection.f, -intersection.s);
			}
			if(intersection.f < 0) {
				array<int, 4> a = {
					-intersection.f, 
					intersection.s, 
					min(x1, x2) * ((int) 10000000) + max(x1, x2), 
					i * 100000 + j
				};
				events.pb(a);
			}
		}
	}
	ld ans = 0;
	ld cur_x = 0;
	sort(events.begin(), events.end(), event_comparison);
	//reverse(all(events));
	for(auto event : events) {
		ld new_x = ((ld) event[0]) / ((ld) event[1]);
		int A = event[3] / 100000;
		int B = event[3] % 100000;

		// dbg(A _ B _ new_x);
		if(covers_zero == 0) {
			ans += new_x - cur_x;
		}
		//swap A, B
		assert(abs(rpos[A] - rpos[B]) == 1);
		if(rpos[A] > rpos[B]) swap(A, B);
		//A B in points array
		int idx = rpos[A];
		int diff = 0;
		if(pts[A].s == 1) diff--;
		else diff++;
		if(pts[B].s == 0) diff--;
		else diff++;
		if(covers[idx] == 0 && diff > 0) covers_zero--;
		if(covers[idx] > 0 && diff == -covers[idx]) covers_zero++;
		covers[idx] += diff;

		rpos[A]++;
		rpos[B]--;
		swap(pos[idx], pos[idx+1]);
		cur_x = new_x;
	}
	if(covers_zero == 0 && canInf) {
		cout << -1 << endl;
	} else {
		cout << fixed << setprecision(12);
		cout << ans << endl;
	}
}
