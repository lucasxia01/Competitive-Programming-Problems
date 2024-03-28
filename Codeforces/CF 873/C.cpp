#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
// added by Lucas
#define trav(a, x) for (auto& a : x)
#define f first
#define s second
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

array<vi, 2> manacher(const string& s) {
	int n = sz(s);
	array<vi,2> p = {vi(n+1), vi(n)};
	rep(z,0,2) for (int i=0,l=0,r=0; i < n; i++) {
		int t = r-i+!z;
		if (i<r) p[z][i] = min(t, p[z][l+t]);
		int L = i-p[z][i], R = i+p[z][i]-!z;
		while (L>=1 && R+1<n && s[L-1] == s[R+1])
			p[z][i]++, L--, R++;
		if (R>r) l=L, r=R;
	}
	return p;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;
        auto ret = manacher(s);
        // form a bunch of segments
        vector<array<int, 3>> segs;
        rep(i, 0, n+1) {
            int len = ret[0][i];
            if (len == 0) continue;
            segs.pb({i+1, 1, i}); // start of segment
            segs.pb({i+len+1, 0, i}); // end of segment
            dbg(i+1, i+len+1);
        }
        sort(all(segs));
        ll ans = 0;
        int dp[n+1]; memset(dp, 0, sizeof dp);

        set<int> heap;
        int j = 0;
        rep(i, 1, n+1) {
            // find the max middle still active
            while (j < sz(segs) && segs[j][0] <= i) {
                if (segs[j][1] == 1) {
                    heap.insert(-segs[j][2]);
                } else {
                    assert(heap.count(-segs[j][2]));
                    heap.erase(-segs[j][2]);
                }
                j++;
            }
            int idx = i%2;
            auto it = heap.begin();
            if (it == heap.end()) continue;
            int val = -(*it);
            int len = i-val;
            int prev = val-len;
            dbg(s, i, val, len, prev);
            assert(prev%2 == idx);
            assert(prev >= 0);
            dp[i] = dp[prev]+1;
            ans += dp[i];
        }
        cout << ans << nl;
    }
}