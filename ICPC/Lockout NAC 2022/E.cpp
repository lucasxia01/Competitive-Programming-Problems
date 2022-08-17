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

ll calc(string s) {
    ll ans = 0;
    trav(c, s) {
        if (c == '.') continue;
        ans *= 10;
        ans += (c-'0');
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string s; cin >> s;
    vector<string> v;
    string t = "";
    F0R(i, sz(s)) {
        if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
            t += s[i];
        } else {
            v.pb(t);
            t = "";
        }
    }
    v.pb(t);
    ll ans = 0;
    trav(u, v) {
        bool ok = 0;
        if (sz(u) >= 4 && u[sz(u)-3] == '.') {
            ok = 1;
        }
        ll temp = calc(u);
        if (!ok) temp *= 100;
        ans += temp;
    }
    vi w;
    w.pb(ans%100);
    ans /= 100;
    while (ans) {
        w.pb(ans%1000);
        ans/=1000;
    }
    reverse(all(w));
    F0R(i, sz(w)-1) {
        if (i != 0 && w[i] < 100) {
            cout << 0;
            if (w[i] < 10) cout << 0;
        }
        cout << w[i];
        if (i == sz(w)-2 && w.back() == 0) continue;
        cout << '.';
    }
    if (w.back() != 0) {
        if (sz(w) == 1) cout << "0.";
        if (w.back() < 10) cout << 0;
        cout << w.back() << nl;
    } else cout << nl;
    return 0;
}
