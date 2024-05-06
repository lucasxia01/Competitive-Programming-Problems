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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        int n; cin >> n;
        // just take 169, 196, 961 and add 0s to them lol
        vector<string> v;
        if (n == 1) {
            cout << 1 << nl;
            continue;
        }
        F0R(i, n/2) {
            string s = "";
            s += '1';
            F0R(j, i) s += '0';
            s += '6';
            F0R(j, i) s += '0';
            s += '9';
            F0R(j, n/2-1 - i) {
                s += '0';
                s += '0';
            }
            v.pb(s);
            dbg(s);
        }
        F0R(i, n/2) {
            string s = "";
            s += '9';
            F0R(j, i) s += '0';
            s += '6';
            F0R(j, i) s += '0';
            s += '1';
            F0R(j, n/2-1 - i) {
                s += '0';
                s += '0';
            }
            v.pb(s);
            dbg(s);
        }
        // add 19600....
        string s = "196";
        F0R(i, n-3) s += '0';
        v.pb(s);
        F0R(i, n) cout << v[i] << nl;
    }
    return 0;
}
