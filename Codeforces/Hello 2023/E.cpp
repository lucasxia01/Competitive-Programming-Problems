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

const int MX = 3e5+5;

int query(int i, string t) {
    cout << "? " << i+1 << " " << t << endl;
    cout.flush();
    int x; cin >> x;
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    string s = ""; F0R(i, n) s += '1';
    // find the ordering
    int cur = 0;
    vpi v;
    F0R(i, n) {
        s[i] = '0';
        int ret = query(i, s);
        v.pb({ret, i});
        s[i] = '1';
    }
    sort(all(v));
    reverse(all(v));

    F0R(i, n) s[i] = '0';
    string ans = s; ans[v[0].s] = '1';
    FOR(i, 1, n-1) {
        int ret = query(v[i].s, ans);
        if (ret) {
            ans[v[i].s] = '1';
            F0R(j, i) ans[v[j].s] = '1';
        }
    }
    cout << "! " << ans << endl;
    cout.flush();
    return 0;
}