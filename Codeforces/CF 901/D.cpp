#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef long double ld;
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
    int n, m; cin >> n >> m;
    ld dp[n+1][m+1]; rep(i, 0, n+1) rep(j, 0, m+1) dp[i][j] = 1e9;
    dp[0][0] = 0;
    rep(i, 0, n) {
        // there are n-i things for this, so max val it can take is m/(n-i)
        rep(j, 0, m+1) { // already used j
            if (dp[i][j] >= 1e9) continue;
            dbg(i, j, dp[i][j]);
            int hi = (m-j)/(n-i);
            rep(jj, 1, min(hi, m-j)+1) {
                ckmin(dp[i+1][j+jj], dp[i][j]+(ld)j/jj);
            }
        }
    }
    cout.precision(10);
    cout << fixed << 2*dp[n][m]+n << nl;
}