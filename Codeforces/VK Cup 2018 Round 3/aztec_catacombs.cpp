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

int n, m;
vi gr[MX];
bool vis[MX], vis2[MX];
vi comp;
set<pi> edges;

void dfs(int v) {
    if (vis[v]) return;
    vis[v] = 1;
    comp.pb(v);
    trav(u, gr[v]) {
        if (u == 1) continue;
        dfs(u);
    }
}

pi dfs2(int start, int v, int p) {
    if (vis2[v]) return {-1, -1};
    vis2[v] = 1;
    // check if there's an edge from v to start
    if (v != start && !edges.count({start, v})) {
        return {p, v};
    }
    trav(u, gr[v]) {
        if (u == 1) continue;
        pi res = dfs2(start, u, v);
        if (res.f != -1) return res;
    }
    return {-1, -1};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    F0R(i, m) {
        int u, v;
        cin >> u >> v;
        gr[u].pb(v);
        gr[v].pb(u);
        edges.insert({u, v});
        edges.insert({v, u});
    }
    // first bfs from 1 to n
    int par[n+1]; F0R(i, n+1) par[i] = -1;
    queue<pi> q;
    q.push({1, 0}); par[1] = 0;
    pi win4 = {-1, -1};
    while (!q.empty()) {
        int u = q.front().f, d = q.front().s;
        q.pop();
        if (d == 2) {
            // we have a path of length 4
            win4 = {par[u], u};
        }
        for (int v : gr[u]) {
            if (par[v] == -1) {
                par[v] = u;
                q.push({v, d+1});
            }
        }
    }
    int ans = MX;
    vi path;
    if (par[n] != -1) {
        int cur = n;
        path.pb(n);
        while (cur != 1) {
            cur = par[cur];
            path.pb(cur);
        }
        ans = sz(path)-1;
        reverse(all(path));

    }
    if (win4.f != -1) {
        if (ckmin(ans, 4)) {
            path = {1, win4.f, win4.s, 1, n};
        }
    } else {
        // now check for 5 by getting components
        bool done = 0;
        FOR(i, 2, n) {
            if (!vis[i] && par[i] != -1) {
                comp.clear();
                dfs(i);
                int N = sz(comp);
                F0R(j, N) {
                    F0R(k, j) {
                        if (!edges.count({comp[j], comp[k]})) {
                            // find the path from comp[j] to comp[k]
                            pi res = dfs2(comp[j], comp[j], 0);
                            assert(res.f != -1);
                            if (ckmin(ans, 5)) {
                                path = {1, comp[j], res.f, res.s, comp[j], n};
                            }
                            done = 1;
                            break;
                        }
                    }
                    if (done) break;
                }
                if (done) break;
            }
        }
    }

    if (ans == MX) cout << -1 << nl;
    else {
        cout << ans << nl;
        trav(x, path) cout << x << " ";
        cout << nl;
    }
    return 0;
}
