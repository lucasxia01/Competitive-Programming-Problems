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
    int r, c; cin >> r >> c;
    char m1[r][c];
    F0R(i, r) F0R(j, c) cin >> m1[i][j];
    char m[max(r, c)][min(r, c)];
    if (r < c) {
        F0R(i, r) F0R(j, c) m[j][i] = m1[i][j];
        // swap and flip
        swap(r, c);
    } else {
        F0R(i, r) F0R(j, c) m[i][j] = m1[i][j];
    }
    // now do rc^2 dp 
    int dp[c][c]; F0R(i, c) F0R(j, c) dp[i][j] = INF;
    F0R(i, r) {
        int pref[c+1]; pref[0] = 0;
        F0R(j, c) pref[j+1] = pref[j] + (m[i][j] == '1');
        // compute something from previous row
        int boxmin[c][c];
        if (i == 0) {
            F0R(j, c) FOR(k, j, c-1) boxmin[j][k] = INF;
            F0R(k, c) boxmin[0][k] = 0;
        } else {
            // should precalc min of dp[i-1][0-j][k] for all k >= j
            int prefmin[c][c]; 
            F0R(k, c) {
                F0R(j, k+2) {
                    if (j == c) continue;
                    if (j == 0) prefmin[j][k] = dp[j][k];
                    else prefmin[j][k] = min(prefmin[j-1][k], dp[j][k]);
                }
            }
            F0R(j, c) FOR(k, j, c-1) {
                if (k == j) {
                    boxmin[j][k] = prefmin[j][k];
                    if (k > 0) ckmin(boxmin[j][k], prefmin[j][k-1]);
                } else boxmin[j][k] = min(boxmin[j][k-1], prefmin[j][k]);
            }
        }
        F0R(j, c) FOR(k, j, c-1) {
            // see how many 1s are in [0, j-1] and [k+1, c-1]
            int tmp1 = pref[j] + pref[c] - pref[k+1]; // j-0 + c-(k+1)
            int tmp2 = (k+1-j)-(pref[k+1]-pref[j]);
            int tmp = tmp1 + tmp2;
            // now find the min of things in the box [0, j] x [j-1, k];
            dp[j][k] = min((int)INF, tmp+boxmin[j][k]);
            dbg(i, j, k, tmp1, tmp2, dp[j][k]);
        }
    }
    int ans = INF;
    F0R(j, c) ckmin(ans, dp[j][c-1]);
    cout << ans << nl;
    
    return 0;
}
