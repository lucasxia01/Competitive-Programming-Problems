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

ll m = -1;
ll solve(ll x, int i, const vi& v) {
    if (i == 0) {
        // test x
        string s = to_string(x);
        // check all substrings
        int n = sz(s);
        F0R(k, n) {
            if (s[k] == '0') continue;
            F0R(j, k+1) {
                // [j, k]
                ll y = stoll(s.substr(j, k-j+1));
                if (y%7 == 0) return 0;
            }
        }
        m = x;
        return 1;
    }
    ll pow = 10;
    if (i-1 < sz(v)) F0R(j, v[i-1]) pow *= 10;
    FOR(j, 1, 6) {
        if (solve(x*pow + j, i-1, v)) return 1;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // 1415, 54, 11, 4, 2, 
    // try to precompute a 10101010101 string 
    // int t; cin >> t;
    // while (t--) {
        int n; cin >> n;
        vi v;
        // decompose into triangular numbers
        while (n) {
            int x = sqrt(2*n);
            x -= 5;
            x = max(0, x);
            while (x*(x+1)/2 <= n) x++;
            x--;
            v.pb(x);
            n -= x*(x+1)/2;
        }
        // assert(sz(v) <= 5);
        string s = "";
        if (sz(v) == 1) {
            F0R(i, v[0]) s += '7';
        } else {
            int a = v[0], b = v[1];
            reverse(v.begin(), v.end());
            v.pop_back(); v.pop_back();
            trav(u, v) cerr << u << nl;
            solve(0, sz(v)+1, v);
            assert(m != -1);
            F0R(i, a) s += '7';
            // middle part hmm
            string tmp = to_string(m);
            F0R(i, sz(tmp)) if (tmp[i] == '0') tmp[i] = '7';
            s += tmp;
            F0R(i, b) s += '7';
        }
        cout << s << nl;
    // }
    return 0;
}
