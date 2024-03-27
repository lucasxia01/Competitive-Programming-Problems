#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
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

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    // int tt; cin >> tt;
    // while (tt--) {
    ll n, c; cin >> n >> c;
    pii p[n]; rep(i,0,n) cin >> p[i].f >> p[i].s;
    ll l = 0, r = (ll)1e9*n/min(n, c) + 1000;
    while (l < r) {
        ll mid = (l + r) / 2;
        // dbg(mid);
        // check if mid resets work
        // we can fully pack in mid*c units
        ll space = 1LL*(mid+1)*c;
        ll T = 0;
        priority_queue<array<int, 3> > pool;
        int left[n];
        rep(i, 0, n) {
            int amt = p[i].f/p[i].s;
            pool.push({p[i].s, amt, i});
            left[i] = p[i].f%p[i].s;
            T += p[i].f;
        }
        int cnt[n]; memset(cnt, 0, sizeof(cnt)); // we can use at most mid+1 amount of each thing
        while (!pool.empty() && space > 0) {
            auto cur = pool.top(); pool.pop();
            int i = cur[2];
            // dbg(i, cnt[i]);
            ll amt = min(space, min(mid+1-cnt[i], 1LL*cur[1]));
            if (amt == 0) continue;
            // dbg("taking", amt, cur[0], cur[1], i);
            cnt[i] += amt;
            T -= 1LL*cur[0]*amt;
            space -= amt;
            if (cnt[i] == p[i].f/p[i].s && left[i] > 0) {
                // unlocks the remaining thing
                // dbg("adding in leftovers", i, left[i]);
                pool.push({left[i], 1, i});
                left[i] = 0;
            }
        }
        int cntMaxUsage = 0;
        ll rest = 0;
        rep(i, 0, n) {
            if (cnt[i] == mid+1) cntMaxUsage++;
            else rest += cnt[i];
        }
        ll over = max(0LL, rest - 1LL*mid*(c-cntMaxUsage));

        dbg(mid, T, space, cntMaxUsage, over);
        bool ok = 0;
        if (T+cntMaxUsage+over <= c) ok = 1;
        if (ok) r = mid;
        else l = mid+1;
    }
    cout << l << nl;
    // }
}