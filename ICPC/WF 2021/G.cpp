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

const ll mod = (119 << 23) + 1, root = 62; // = 998244353

ll modpow(ll b, ll e) {
    ll ans = 1;
    for (; e; b = b * b % mod, e /= 2)
        if (e & 1) ans = ans * b % mod;
    return ans;
}
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
typedef vector<ll> vl;
void ntt(vl &a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vl rt(2, 1);
    for (static int k = 2, s = 2; k < n; k *= 2, s++) {
        rt.resize(n);
        ll z[] = {1, modpow(root, mod >> s)};
        rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
    }
    vi rev(n);
    rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
            ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
            a[i + j + k] = ai - z + (z > ai ? mod : 0);
            ai += (ai + z >= mod ? z - mod : z);
        }
}
vl conv(const vl &a, const vl &b) {
    if (a.empty() || b.empty()) return {};
    int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s),
        n = 1 << B;
    int inv = modpow(n, mod - 2);
    vl L(a), R(b), out(n);
    L.resize(n), R.resize(n);
    ntt(L), ntt(R);
    rep(i,0,n)
        out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
    ntt(out);
    return {out.begin(), out.begin() + s};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int r, c; cin >> r >> c;
    int a[r][c]; rep(i, 0, r) rep(j, 0, c) cin >> a[i][j];
    int n, m; cin >> n >> m;
    int b[n][m]; rep(i, 0, n) rep(j, 0, m) cin >> b[i][j];
    if (r > n || c > m) {
        cout << 0 << nl;
        return 0;
    }
    vector<bool> mask(n*m, true);
    // map each number to a random number
    ll val[101]; rep(i, 1, 101) val[i] = rng()%mod;
    val[0] = 0;
    vl vecA(r*m, 0), vecB(n * m, 0);
    ll total = 0;
    rep(i, 0, r) rep(j, 0, c) {
        vecA[i * m + j] = val[a[i][j]];
        total += (1LL*val[a[i][j]]*val[a[i][j]])%mod;
        total %= mod;
    }
    rep(i, 0, n) rep(j, 0, m) vecB[i * m + j] = val[b[i][j]];
    reverse(all(vecB));
    vl ret = conv(vecA, vecB);
    rep(i, 0, n*m) mask[i] = (mask[i] && (ret[i] == total));

    // check all the valid ones
    vector<pii> ans;
    rep(i, 0, n-r+1) rep(j, 0, m-c+1) {
        int idx = n*m-1 - (i*m + j);
        if (mask[idx]) ans.emplace_back(i, j);
    }
    cout << sz(ans) << nl;
    trav(a, ans) cout << a.f+1 << ' ' << a.s+1 << nl;
}