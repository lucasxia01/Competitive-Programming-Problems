#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
using ld = long double;
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
void dbg_out() { cerr << nl; }
template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) cerr << #__VA_ARGS__ << ":", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

// seems like kactl is missing rng
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int k, m;
ll n;
ll kminus1fac = 1;
int a[10];
int vals[10];
ld ans = 0;
ld T = 1;
void comp(int idx, int left) {
    if (idx == m-1) {
        if (left > a[idx]) return;
        // compute the total and 
        vals[idx] = left;
        int rem[m]; rep(i, 0, m) rem[i] = a[i]-vals[i];
        ld total = 1;
        rep(i, 0, m) {
            rep(j, 0, vals[i]) { // a[i] C vals[i]
                total *= (a[i]-j);
                total /= (j+1);
            }
        }
        
        ld cur = 0;
        rep(i, 0, m) {
            cur += (ld)vals[i] * kminus1fac / (rem[i]+1);
        }
        cur = min(cur, (ld)1);
        ans += cur * total/T;
        return;
    }
    rep(i, 0, min(left, a[idx])+1) {
        vals[idx] = i;
        comp(idx+1, left-i);
    }
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    cin >> k >> m;
    rep(i, 0, m) cin >> a[i];
    rep(i, 1, k) kminus1fac *= i;
    rep(i, 0, m) n += a[i];
    rep(i, 0, k) {
        T *= (n-i);
        T /= (i+1);
    }
    comp(0, k);
    cout.precision(12);
    cout << fixed << ans << nl;
}