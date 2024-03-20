#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
#define int ll
typedef pair<int, int> pii;
typedef vector<int> vi;

// added by Lucas
#define trav(a, x) for (auto& a : x)
#define f first
#define s second
#define mp make_pair
#define pb push_back
const char nl = '\n';

// stretching it a little
template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

#ifdef DBG
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) cerr << #__VA_ARGS__ << ":", dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

// seems like kactl is missing rng
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 2e5+5;

using T = pair<pii, int>;
static constexpr T unit = {{-1, -1}, -1};
template<class T>
struct RMQ {
    T f(T a, T b) { 
        if (a.f.s == b.f.s) {
            return {a.f, max(a.s, b.s)};
        } else if (a.f.f >= b.f.f) {
            return {a.f, max(b.f.f, a.s)};
        } else {
            return {b.f, max(a.f.f, b.s)};
        }
    }
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = f(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		// assert(a < b); // or return inf if a == b
        if (a == b) return unit;
		int dep = 31 - __builtin_clz(b - a);
		return f(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

signed main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int h[n]; rep(i, 0, n) cin >> h[i];
        int a[n]; rep(i, 0, n) cin >> a[i];
        int m = *max_element(a, a+n);
        vector<array<int, 3> > v; rep(i, 0, n) v.pb({a[i], h[i], i});
        sort(all(v));
        vector<T> V;
        rep(i, 0, n) V.pb({{v[i][1], v[i][2]}, 0});
        RMQ<T> rmq(V);
        // now try for all x from 1 to max ai
        ll ans[n]; rep(i, 0, n) ans[i] = 0;
        // precompute all lower_bounds up to 2*m+5 on v
        int M = 2*m+5;
        int idx[M];
        rep(i, 1, M) {
            idx[i] = lower_bound(all(v), array<int, 3>{i, -1LL, -1LL})-v.begin();
        }
        rep(x, 1, m+2) {
            // group all the a[i] in groups of x with binary search or smth
            pair<pair<ll, int>, ll> best = unit;
            for (int i = 0; x*i+1 <= m; i++) {
                // range is (x*i, x*(i+1)] or [x*i+1, x*(i+1)+1)
                int l_idx = idx[x*i+1];
                int r_idx = idx[x*(i+1)+1];
                // dbg(l_idx, r_idx);
                pair<pair<ll, int>, ll> hiH = rmq.query(l_idx, r_idx);
                hiH.f.f *= i+1; // this is what ceil(a[i]/x) is
                hiH.s *= i+1;
                // dbg(i+1, hiH.f.f, hiH.s);
                best = rmq.f(best, hiH);
            }
            // see where the best was from
            // dbg(x, best.f.s, best.f.f, best.s);
            if (best.f.s == -1) continue;
            ckmax(ans[best.f.s], best.f.f-best.s);
        }
        rep(i, 0, n) cout << ans[i] << " ";
        cout << nl;
    }
}