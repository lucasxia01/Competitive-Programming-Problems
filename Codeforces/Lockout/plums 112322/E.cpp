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
#define dbg(...) dbg_out(__VA_ARGS__);ut<<"}"; return out;
#else
#define dbg(...)

#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int a[n]; F0R(i, n) cin >> a[i];
    int cur = 0;
    int l = 0, r = n-1;
    string ans = "";
    while (l <= r) {
        if (a[l] == a[r]) {
            if (a[l] <= cur) break;
            int best = 0;
            int cnt = 1;
            int k = l+1;
            while (k <= r && a[k] > a[k-1]) {
                cnt++;
                k++;
            }
            best = cnt;

            cnt = 1;
            k = r-1;
            while (k >= l && a[k] > a[k+1]) {
                cnt++;
                k--;
            }
            if (ckmax(best, cnt)) {
                F0R(K, best) ans += 'R';
            } else {
                F0R(K, best) ans += 'L';
            }
            break;
        } else {
            if (a[l] < a[r]) {
                if (a[l] > cur) {
                    ans += 'L'; cur = a[l++];
                } else if (a[r] > cur) {
                    ans += 'R'; cur = a[r--];
                } else {
                    break;
                }
            } else {
                if (a[r] > cur) {
                    ans += 'R'; cur = a[r--];
                } else if (a[l] > cur) {
                    ans += 'L'; cur = a[l++];
                } else {
                    break;
                }
            }
        }
    }
    cout << sz(ans) << nl << ans << nl;
    return 0;
}
