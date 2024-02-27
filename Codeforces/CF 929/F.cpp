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
        int n, m; cin >> n >> m;
        int pref[n+1]; pref[0] = 0;
        bool a[n][m]; F0R(i, n) F0R(j, m) cin >> a[i][j];
        F0R(i, n) pref[i+1] = pref[i]+a[i][m-1];
        // can move down 2 or down 1, right 1
        // just bfs from 0, 0
        int vis[n][m]; F0R(i, n) F0R(j, m) vis[i][j] = -1;
        queue<pi> q;
        q.push({0, 0});
        vis[0][0] = 0;
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            dbg(x, y, vis[x][y]);
            if (y == m-1) continue;
            // try going down
            if (!a[(x+1)%n][y] && !a[(x+2)%n][y]) {
                if (vis[(x+2)%n][y] == -1) {
                    vis[(x+2)%n][y] = vis[x][y] + 1;
                    q.push({(x+2)%n, y});
                }
            }
            // try going down and right
            if (!a[(x+1)%n][y+1] && vis[(x+1)%n][y+1] == -1) {
                vis[(x+1)%n][y+1] = vis[x][y] + 1;
                q.push({(x+1)%n, y+1});
            }
        }
        // now go to end
        int ans = INF;
        F0R(i, n) {
            if (vis[i][m-1] != -1) {
                int T = vis[i][m-1];
                // time is vis[i][m-1], so we really ended at (i-T, m-1)
                int x = ((i-T)%n+n)%n;
                int dist = n-1-x;
                dbg(T, x, dist);
                ckmin(ans, T+(x+1)%n);
                if (x == n-1) continue;
                // or we can try going downward from (x, m-1) to (n-1, m-1)
                // requires n-1-x moves if there are not any rocks from (x, m-1) to (n-1, m-1) and (0, m-1) to (n-1-x-1, m-1) at time T
                // so at time 0, we don't want any rocks from (x+T, m-1) to (n-1-x-1+T, m-1)
                if (dist*2 >= m-1) {
                    // then we want NO ROCKS
                    if (pref[n] == 0) {
                        ckmin(ans, T+dist);
                    }
                    continue;
                }
                int l = (x+T)%n;
                int r = (n-1-x-1+T)%n;
                if (l < r) {
                    if (pref[r+1]-pref[l] == 0) {
                        ckmin(ans, T+dist);
                    }
                } else {
                    if (pref[r+1] == 0 && pref[n]-pref[l] == 0) {
                        ckmin(ans, T+dist);
                    }
                }
            }
        }
        if (ans == INF) cout << -1 << nl;
        else cout << ans << nl;
    }
    return 0;
}
