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

vi solve(const vi& a, int bit) {
    if (sz(a) == 0) return {};
    // we know all of a is under (1LL<<bit)
    // assume a is sorted
    // find the part of a that is under (1LL<<(bit-1))
    if (bit == 0) {
        assert(sz(a) == 1 && a[0] == 0);
        return {0};
    }
    vi small, big;
    int j = 0;
    while (j < sz(a) && a[j] < (1LL<<(bit-1))) {
        small.pb(a[j]);
        j++;
    }
    int jj = j;
    while (j < sz(a)) {
        assert(a[j]&(1LL<<(bit-1)));
        big.pb(a[j]^(1LL<<(bit-1)));
        j++;
    }
    vi ret = solve(small, bit-1); // small part solved
    vi bigret = solve(big, bit-1);
    assert(sz(ret) == jj);
    assert(sz(bigret) == sz(a)-jj);
    // dbg(bit);
    // trav(x, a) cerr << x << ' ';
    // cerr << nl;
    // cerr << "smalllret: "; trav(x, ret) cerr << x << ' ';
    // cerr << nl;
    // cerr << "bigret: "; trav(x, bigret) cerr << x << ' ';
    // cerr << nl;
    j = 0;
    int JJ = jj;
    while (jj < sz(a)) {
        while (a[j] != (a[jj]^(1LL<<(bit-1)))) j++;
        assert(j < sz(ret));
        assert(jj-JJ < sz(bigret));
        bigret[jj-JJ] ^= (1LL<<(bit-1));
        swap(ret[j], bigret[jj-JJ]);
        jj++;
    }
    ret.insert(ret.end(), all(bigret));
    // dbg("returning");
    // trav(x, ret) cerr << x << ' ';
    // cerr << nl;
    return ret;
}
signed main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    map<int, int> m;
    rep(i, 0, n) {
        cin >> a[i];
        m[a[i]] = i;
    }
    sort(all(a));
    vi ret = solve(a, 60);
    vi b(n);
    rep(i, 0, n) {
        b[m[a[i]]] = ret[i];
    }
    rep(i, 0, n) cout << b[i] << nl;
}