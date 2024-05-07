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
    ll total = 0;
    while (!cin.eof()) {
        string s; cin >> s;
        reverse(all(s));
        map<char, int> m;
        m['2'] = 2;
        m['1'] = 1;
        m['0'] = 0;
        m['-'] = -1;
        m['='] = -2;

        

        ll cur = 0;
        ll pow = 1;
        trav(c, s) {
            cur += pow * m[c];
            pow *= 5;
        }
        dbg(cur);
        total += cur;
    }
    map<int, char> rev;
    rev[2] = '2';
    rev[1] = '1';
    rev[0] = '0';
    rev[-1] = '-';
    rev[-2] = '=';
    string s = "";
    while (total) {
        int cur = total%5;
        if (cur > 2) cur -= 5;
        s += rev[cur];
        total -= (cur);
        total /= 5;
    }
    reverse(all(s));
    cout << s << nl;
    return 0;
}
