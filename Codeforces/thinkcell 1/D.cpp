#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
#define int ll

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string s; cin >> s;
        ll total = 0;
        ll dp[n]; F0R(i, n) dp[i] = 0; // number of starting places that end here
        F0R(i, n) {
            if (s[i] == '1') {
                if (i >= 3) {
                    char a = s[i-3], b = s[i-2], c = s[i-1];
                    if (c == '0' && b == '0') {
                        dp[i] = dp[i-3]+dp[i-2]+dp[i-1];
                    } else if (c == '0' && b == '1' && a == '0') {
                        dp[i] = dp[i-1];
                    } else if (c == '0' && b == '1' && a == '1') {
                        dp[i] = dp[i-1]+dp[i-3];
                    } else if (c == '1' && b == '0' && a == '0') {
                        dp[i] = 0;
                    } else if (c == '1' && b == '0' && a == '1') {
                        dp[i] = dp[i-3];
                    } else if (c == '1' && b == '1' && a == '0') {
                        dp[i] = 0;
                    } else if (c == '1' && b == '1' && a == '1') {
                        dp[i] = dp[i-3];;
                    }
                } else if (i == 2){ // i is 0, 1, 2
                    char a = s[i-2], b = s[i-1];
                    if (b == '0' && a == '0') {
                        dp[i] = 2;
                    } else if (b == '0') dp[i] = 1;
                } else if (i == 1) {
                    if (s[i-1] == '0') {
                        dp[i] = 1;
                    }
                }
            } else {
                if (i >= 3) {
                    char a = s[i-3], b = s[i-2], c = s[i-1];
                    if (a == '1') dp[i] = dp[i-3];
                    else if (c == '0' && b == '0' && a == '0') dp[i] = dp[i-3];
                }
            }
            dp[i]++;
            dbg(i, dp[i]);
            // check if placing at i is good
            if (s[i] == '0') continue;
            // just check all previous j lol
            int cntL = 0;
            // F0R(j, i) {
            //     // check if starting at j would lead to i
            //     int k = j;
            //     while (k < i) {
            //         if (s[k] == '1') k += 3;
            //         else k++;
            //     }
            //     if (k == i) cntL++;
            // }
            dbg(i, cntL+1, dp[i], n-i);
            // assert(dp[i] == cntL+1);
            total += dp[i]*(n-i);
        }
        // handle the 101s separately
        // 101 -> 111
        cout << total << nl;
    }
    return 0;
}
