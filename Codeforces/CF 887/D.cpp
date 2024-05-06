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

const int MX = 6e5+5;

bool check(vpi& v, int x) {
    trav(p, v) {
        if (x >= p.f && x <= p.s) return true;
    }
    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        string s; cin >> s;
        F0R(i, n-1) if (s[i] != s[i+1]) k--;
        // store ranges
        vpi dp[n][2];
        int x = (s[0] == 'B');
        dp[0][0].pb({x, x});
        dp[0][1].pb({1-x, 1-x});
        FOR(i, 1, n-1) {
            
            if (s[i] == 'A') { // its an A
                trav(p, dp[i-1][0]) dp[i][0].pb(p);
                trav(p, dp[i-1][1]) dp[i][0].pb({p.f+1, p.s+1});

                trav(p, dp[i-1][0]) dp[i][1].pb({p.f+2, p.s+2});
                trav(p, dp[i-1][1]) dp[i][1].pb({p.f+1, p.s+1});
            } else { // its a B
                trav(p, dp[i-1][0]) dp[i][0].pb({p.f+1, p.s+1});
                trav(p, dp[i-1][1]) dp[i][0].pb({p.f+2, p.s+2});

                trav(p, dp[i-1][0]) dp[i][1].pb({p.f+1, p.s+1});
                trav(p, dp[i-1][1]) dp[i][1].pb({p.f, p.s});
            }
            // now sort and collapse
            F0R(j, 2) {
                dbg(i, j);
                sort(all(dp[i][j]));
                vpi tmp; tmp.pb({dp[i][j][0]});
                trav(p, dp[i][j]) {
                    if (p.f > tmp.back().s+1) {
                        tmp.pb(p);
                    } else {
                        ckmax(tmp.back().s, p.s);
                    }
                }
                // trav(p, tmp) {
                //     cerr << "(" << p.f << "," << p.s << "), ";
                // }
                // cerr << nl;
                dp[i][j] = tmp;
            }
        }
        bool ok = 0;
        int idx = -1;
        if (check(dp[n-1][0], k)) {
            ok = 1;
            idx = 0;
        } else if (check(dp[n-1][1], k)) {
            ok = 1;
            idx = 1;
        }
        if (!ok) cout << "NO" << nl;
        else {
            cout << "YES" << nl;
            string ans = "";
            if (idx == 0) ans += 'A';
            else ans += 'B';

            F0Rd(i, n-1) {
                if (idx == 0) {
                    if (s[i+1] == 'A') {
                        if (check(dp[i][0], k)) {
                            k = k;
                            idx = 0;
                        } else if (check(dp[i][1], k-1)) {
                            k = k-1;
                            idx = 1;
                        }
                    } else {
                        if (check(dp[i][0], k-1)) {
                            k = k-1;
                            idx = 0;
                        } else if (check(dp[i][1], k-2)) {
                            k = k-2;
                            idx = 1;
                        }
                    }
                    
                } else {
                    if (s[i+1] == 'A') {
                        if (check(dp[i][0], k-2)) {
                            k = k-2;
                            idx = 0;
                        } else if (check(dp[i][1], k-1)) {
                            k = k-1;
                            idx = 1;
                        }
                    } else {
                        if (check(dp[i][0], k-1)) {
                            k = k-1;
                            idx = 0;
                        } else if (check(dp[i][1], k)) {
                            k = k;
                            idx = 1;
                        }
                    }
                }

                if (idx == 0) ans += 'A';
                else ans += 'B';
            }
            reverse(all(ans));
            cout << ans << nl;
        }
    }
    return 0;
}
