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

const int MX = 3e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, k, p; cin >> n >> k >> p;
        int dp[n+1][k+1][3]; // instead store the difference and not the
        F0R(i, n+1) F0R(j, k+1) F0R(l, 3) dp[i][j][l] = 0;
        dp[0][0][0] = 1;
        F0R(i, n) F0R(j, k+1) {
            F0R(l, 3) {
                if (dp[i][j][l] == 0) continue;
                if (l == 0) {
                    // go above for state 1
                    // equal and below for state 0
                    F0R(jj, j+1) {
                        dp[i+1][jj][0] += dp[i][j][l];
                        dp[i+1][jj][0] %= p;
                    }
                    FOR(jj, j+1, k) {
                        dp[i+1][jj][1] += dp[i][j][l];
                        dp[i+1][jj][1] %= p;
                    }
                } else if (l == 1) {
                    // go down ENOUGH for state 2
                    int cur = 0;
                    assert(i >= 1);
                    F0Rd(jj, j) {
                        cur += dp[i-1][j-jj-1][0];
                        cur %= p;
                        cur += dp[i-1][j-jj-1][1];
                        cur %= p;
                        // we need everything below j-jj from i-1
                        dp[i+1][jj][2] += cur;
                        dp[i+1][jj][2] %= p;
                        // the rest goes to state 0?
                    }
                    cur = 0;
                    F0R(jj, j) {
                        dp[i+1][jj][0] += cur;
                        dp[i+1][jj][0] %= p;
                        cur += dp[i-1][j-jj-1][0];
                        cur %= p;
                        cur += dp[i-1][j-jj-1][1];
                        cur %= p;
                    }
                    dp[i+1][j][0] += dp[i][j][l];
                    dp[i+1][j][0] %= p;
                    FOR(jj, j+1, k) {
                        dp[i+1][jj][1] += dp[i][j][l];
                        dp[i+1][jj][1] %= p;
                    }
                } else {
                    // once we're in state 2, we're done
                    F0R(jj, k+1) {
                        dp[i+1][jj][2] += dp[i][j][l];
                        dp[i+1][jj][2] %= p;
                    }
                }
            }
        }
        int ans2 = 0, ans1 = 0, ans = 0;
        F0R(j, k+1) {
            ans2 += dp[n][j][2];
            ans2 %= p;
            ans1 += dp[n][j][1]; // ending in state 1 is also fine
            ans1 %= p;
        }
        dbg(ans1, ans2);
        ans = (ans1+ans2)%p;
        int total = 1; // (k+1)^n
        F0R(i, n) total = (1LL*total * (k+1)) % p;
        ans = ((total-ans)%p+p)%p;
        cout << ans << nl;
    }
    return 0;
}
