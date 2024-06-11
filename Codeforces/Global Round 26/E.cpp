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

const int MX = 2e5+5;

vi gr[MX];
int dp[MX][2][2]; // node v, whether v is a leaf, whether subtree has the first root
int n;
void solve(int v, int p) {
    // see if this node forms a new leaf
    if (sz(gr[v]) == 1) {
        dp[v][0][0] = 0;
        dp[v][1][0] = 1;
        dp[v][0][1] = dp[v][1][1] = 0;
    } else {
        dp[v][0][0] = dp[v][0][1] = 0;
        dp[v][1][0] = dp[v][1][1] = 1;
    }
    trav(u, gr[v]) {
        if (u == p) continue;
        solve(u, v);
        dp[v][1][1] = min(dp[v][1][1] + min(dp[u][0][0], dp[u][1][0]), 
                          dp[v][1][0] + min(dp[u][0][1], dp[u][1][1]));
        dp[v][1][0] += min(dp[u][0][0], dp[u][1][0]);

        dp[v][0][1] = min(dp[v][0][1] + dp[u][1][0], dp[v][0][0] + dp[u][1][1]);
        dp[v][0][0] += dp[u][1][0];
    }
    // dp[v][0] = we look at dp[u][] where at least 1 thing is alive
    dbg(v+1, dp[v][0][0], dp[v][1][0], dp[v][0][1], dp[v][1][1]);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        F0R(i, n) gr[i].clear();
        F0R(i, n) F0R(j, 2) F0R(k, 2) dp[i][j][k] = 0;
        F0R(i, n-1) {
            int u, v; cin >> u >> v;
            --u, --v;
            gr[u].pb(v);
            gr[v].pb(u);
        }
        if (n == 2) {
            cout << 2 << nl;
            continue;
        }
        F0R(i, n) if (sz(gr[i]) > 1) {
            solve(i, -1);
            cout << n-min(dp[i][0][1], dp[i][1][1]) << nl;
            break;
        }
    }
    return 0;
}
