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
const short INF = 805;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

/**** Credit to chatgpt 4.0 ****/

// Stream operator for std::pair
template<typename T1, typename T2>
ostream& operator<<(ostream &out, const pair<T1, T2> &v) {
    out << "(" << v.first << ", " << v.second << ")"; 
    return out;
}

// Trait to check if a type is iterable
template<typename T, typename = void>
struct is_iterable : false_type {};

template<typename T>
struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type {};

// Stream operator for iterable types excluding std::string
template<typename TT>
typename enable_if<is_iterable<TT>::value && !is_same<TT, string>::value, ostream&>::type
operator<<(ostream& out, const TT& c) {
    out << "{ ";
    for (const auto& x : c) out << x << " ";
    out << "}"; 
    return out;
}

template<typename T>
ostream& operator<<(ostream& out, std::stack<T> container) {
    std::vector<T> elements;
    while (!container.empty()) {
        elements.push_back(container.top());
        container.pop();
    }
    std::reverse(elements.begin(), elements.end()); // Reverse to maintain order
    return out << elements;
}

template<typename T>
ostream& operator<<(ostream& out, std::queue<T> container) {
    std::vector<T> elements;
    while (!container.empty()) {
        elements.push_back(container.front());
        container.pop();
    }
    return out << elements;
}

// Helper function to print std::priority_queue
template<typename T, typename Container, typename Compare>
ostream& operator<<(ostream& out, std::priority_queue<T, Container, Compare> pq) {
    out << "{";
    while (!pq.empty()) {
        out << " " << pq.top();
        pq.pop();
    }
    out << " }";
    return out;
}

#ifdef DBG
void dbg_out() { cerr << endl; }

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}

#define dbg(...) cerr << #__VA_ARGS__ << ":", dbg_out(__VA_ARGS__);
#define dbg_array(a, n) cerr << #a << ": { "; for(int i = 0; i < n; i++) cerr << a[i] << " "; cerr << "}\n";
#else
#define dbg(...)
#define dbg_array(a, n)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 800;

short dp[MX+1][MX+1]; // l, r, c, range [l, r) and color c

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vi a(n+1); 
    map<int, int> s;
    a[n] = 0;
    s.insert({0, -1});
    F0R(i, n) {
        cin >> a[i];
        s.insert({a[i], -1});
    }
    // compress colors
    int m = sz(s);
    int ii = 0;
    trav(c, s) c.s = ii++;
    F0R(i, n) a[i] = s[a[i]];
    // find next occurrence of each color
    int last[m]; F0R(i, m) last[i] = n+1;
    last[0] = n;
    int nxt[n];
    F0Rd(i, n) {
        nxt[i] = last[a[i]];
        last[a[i]] = i;
    }
    F0R(i, n) FOR(j, i+1, n) dp[i][j] = INF;
    F0R(i, n+1) dp[i][i] = 0;
    // start as all 0
    // assume that for a range, we NEVER start with the set color k
    // and we always end one before the set color k
    F0Rd(i, n) FOR(j, i+1, n) {
        int k = a[j];
        if (k == a[i]) {
            dp[i][j] = dp[i+1][j];
            dbg("short", i, j, k, dp[i][j]);
            continue;
        }
        // replace with color a[i]
        short tmp = dp[i+1][j]+1;
        ckmin(dp[i][j], tmp);
        int jj = nxt[i];
        while (jj < j) {
            tmp = dp[i+1][jj]+dp[jj+1][j]+(short)1;
            ckmin(dp[i][j], tmp);
            jj = nxt[jj];
        }
        dbg(i, j, k, dp[i][j]);
    }
    cout << dp[0][n] << nl;
    return 0;
}