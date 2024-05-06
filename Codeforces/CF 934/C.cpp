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

template <class T, class G>
auto tree_shortest_paths(const G& g, int s) {
    std::vector d(g.size(), std::numeric_limits<T>::max());
    std::vector prv(g.size(), -1);
    auto dfs = [&](auto self, int u, int p, T dist) -> void {
        prv[u] = p;
        d[u] = dist;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u, dist + 1);
        }
    };
    dfs(dfs, s, -1, 0);
    return std::make_pair(d, prv);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<vector<int>> g(n);
        F0R(i, n-1) {
            int u, v; cin >> u >> v;
            --u, --v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        auto [d, prv] = tree_shortest_paths<int>(g, 0);
        int l = int(max_element(begin(d), end(d)) - begin(d));
        tie(d, prv) = tree_shortest_paths<int>(g, l);
        int r = int(max_element(begin(d), end(d)) - begin(d));
        vector<int> path;
        for (int i = r; i != -1; i = prv[i]) path.push_back(i);
        reverse(begin(path), end(path));
        dbg(path);
        // if path is odd, spam the middle
        int len = sz(path);
        vpi ans;
        if (len%2 == 1) {
            F0R(i, len/2+1) {
                ans.emplace_back(path[len/2], i);
            }
        } else {
            if (len%4 == 0) {
                // spam the two centers
                FOR(i, 1, len/4) {
                    ans.emplace_back(path[len/2], 2*i-1);
                    ans.emplace_back(path[len/2-1], 2*i-1);
                }
            } else {
                F0R(i, len/2+1) {
                    ans.emplace_back(path[len/2], i);
                }
            }
        }
        cout << sz(ans) << nl;
        trav(p, ans) {
            cout << p.first+1 << " " << p.second << nl;
        }
    }
    return 0;
}
