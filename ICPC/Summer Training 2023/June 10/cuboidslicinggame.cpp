#include <bits/stdc++.h>

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
#define rep(i, a, b) for(int i = a; i < (b); ++i)

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
#define dbg(...) dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 31;
int dp[MX][MX][MX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    rep(i, 1, MX) rep(j, 1, MX) rep(k, 1, MX) {
        if (i > j || j > k) continue;
        // try all valid moves
        vi v;
        rep(ii, 1, (i+1)/2+1) rep(jj, 1, (j+1)/2+1) rep(kk, 1, (k+1)/2+1) {
            // ii-1 or i-ii
            vi vv = {
                    dp[ii-1][jj-1][kk-1],
                    dp[ii-1][jj-1][k-kk],
                    dp[ii-1][j-jj][kk-1],
                    dp[ii-1][j-jj][k-kk],
                    dp[i-ii][jj-1][kk-1],
                    dp[i-ii][jj-1][k-kk],
                    dp[i-ii][j-jj][kk-1],
                    dp[i-ii][j-jj][k-kk]
            };
            int res = 0;
            for (int u : vv) {
                res ^= u;
            }
            v.pb(res);
        }
        // find mex
        sort(all(v));
        int c = 0;
        int l = 0;
        while (1) {
            while (l < sz(v) && v[l] < c) {
                l++;
            }
            if (l < sz(v) && v[l] == c)
                c++;
            else break;
        }
        dp[i][j][k] = dp[i][k][j] = dp[j][i][k] = dp[j][k][i] = dp[k][i][j] = dp[k][j][i] = c;
    }
    string s; cin >> s;
    string t = (s == "RUBEN" ? "ALBERT" : "RUBEN");
    int x = 0;
    int n; cin >> n;
    rep(i, 0, n) {
        int a, b, c; cin >> a >> b >> c;
        x ^= dp[a][b][c];
    }
    cout << (x ? s : t) << endl;
    return 0;
}