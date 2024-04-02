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
        int n, k; cin >> n >> k;
        int cost[n+1][n+1]; F0R(i, n+1) F0R(j, n+1) cost[i][j] = INF;
        F0R(i, n) F0R(j, n-i) cin >> cost[i+1][i+1+j];
        vi dp1[n+1]; // k best things that end at i
        vi dp2[n+1]; // k best things that DONT end at i
        dp2[0].pb(0);
        int total = 1;
        FOR(i, 1, n) {
            // dp2[i] is merge of dp1[i-1] and dp2[i-1];
            dp2[i] = dp2[i-1];
            trav(u, dp1[i-1]) {
                dp2[i].pb(u);
            }
            sort(all(dp2[i]));
            reverse(all(dp2[i]));
            if (sz(dp2[i]) > k) dp2[i].resize(k); // truncate to k

            // for everything that ended BEFORE i-1
            int ptr[i]; memset(ptr, 0, sizeof ptr);
            priority_queue<pi> pq;
            // int best[i+1]; F0R(j, i+1) best[j] = -INF;
            F0Rd(j, i) {
                // best[j] = max(best[j+1], cost[j+1][i]);
                if (ptr[j] < sz(dp2[j])) {
                    // not just cost[j+2][i]
                    // also can consider cost[j+3][i], cost[j+4][i], etc
                    pq.push({dp2[j][ptr[j]]+cost[j+1][i], j});
                    ptr[j]++; // move to next one
                }
            }
            int iters = k;
            // but we might need more iterations to make up for the rest
            if (total < k) ckmax(iters, total-k);
            dbg(i, iters);
            F0R(it, iters) { // k iterations
                // if its empty, abort
                if (pq.empty()) break;
                auto [val, j] = pq.top(); pq.pop();
                dbg(i, val, j);
                dp1[i].pb(val);
                if (ptr[j] < sz(dp2[j])) {
                    pq.push({dp2[j][ptr[j]]+cost[j+1][i], j});
                    ptr[j]++;
                }
            }
            sort(all(dp1[i]));
            reverse(all(dp1[i]));
            total += sz(dp1[i]);
            dbg(i, sz(dp1[i]), sz(dp2[i]));
            dbg(dp1[i], dp2[i]);
        }
        vi ans;
        trav(u, dp1[n]) ans.pb(u);
        trav(u, dp2[n]) ans.pb(u);
        
        dbg(sz(ans));
        sort(all(ans));
        reverse(all(ans));
        assert(sz(ans) >= k);
        F0R(i, k) cout << ans[i] << ' ';
        cout << nl;
    }
    return 0;
}
