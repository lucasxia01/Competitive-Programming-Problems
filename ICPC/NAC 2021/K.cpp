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

const int MX = 301;

bool naive_check(int a, int b, int x, int y) {
    if (abs(a-x)+abs(b-y) == 1) return 1;
    if (abs(a-x) <= 1 || abs(b-y) <= 1) return 0;
    return 1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // precompute the nimbers
    int nimber[MX][MX]; rep(i, 0, MX) rep(j, 0, MX) nimber[i][j] = -1;
    rep(i,1,MX) {
        rep(j,1,MX) {
            if (nimber[i][j] != -1) continue;
            if (abs(i-j) <= 1) continue;
            // try move either one
            vector<bool> seen(2*MX, 0);
            rep(ii, 1, i) {
                if (abs(ii-j) <= 1) continue;
                assert(nimber[ii][j] != -1);
                seen[nimber[ii][j]] = 1;
            }
            rep(jj, 1, j) {
                if (abs(i-jj) <= 1) continue;
                seen[nimber[i][jj]] = 1;
            }
            nimber[i][j] = 0;
            while (seen[nimber[i][j]]) nimber[i][j]++;
            dbg(i, j, nimber[i][j]);
        }
    }
    int t; cin >> t;
    while (t--) {
        int a, b, x, y; cin >> a >> b >> x >> y;
        // handle specially if within 1 in either coordinate
        int ii = a-1;
        int ans = 0;
        while (ii > 0) {
            if (ii == x && b == y) break;
            int val = nimber[ii][x];
            int val2 = nimber[b][y];
            dbg(ii, x, b, y, val, val2, (val^val2), naive_check(ii, b, x, y));
            if (naive_check(ii, b, x, y) && !(val^val2)) ans++;
            ii--;
        }
        ii = x-1;
        while (ii > 0) {
            if (a == ii && b == y) break;
            int val = nimber[a][ii];
            int val2 = nimber[b][y];
            dbg(a, b, ii, y, val, val2, (val^val2), naive_check(a, b, ii, y));
            if (naive_check(a, b, ii, y) && !(val^val2)) ans++;
            ii--;
        }
        int jj = b-1;
        while (jj > 0) {
            if (a == x && jj == y) break;
            int val = nimber[a][x];
            int val2 = nimber[jj][y];
            dbg(a, jj, x, y, val, val2, (val^val2), naive_check(a, jj, x, y));
            if (naive_check(a, jj, x, y) && !(val^val2)) ans++;
            jj--;
        }
        jj = y-1;
        while (jj > 0) {
            if (a == x && b == jj) break;
            int val = nimber[a][x];
            int val2 = nimber[b][jj];
            dbg(a, x, b, jj, val, val2, (val^val2), naive_check(a, b, x, jj));
            if (naive_check(a, b, x, jj) && !(val^val2)) ans++;
            jj--;
        }
        cout << ans << nl;
    }
    return 0;
}
