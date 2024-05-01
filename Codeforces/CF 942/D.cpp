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

const int MX = 1e6+5;

int n, m;
int root[MX]; // root cycle node of each node
int height[MX]; // height of each node in the tree
int tin[MX], tout[MX]; // time in and time out of each node in the tree
int cycle[MX]; // cycle number for each cycle node
int cycleRank[MX]; // rank of each cycle node in the cycle
int cycleSize[MX]; // size of each cycle
int nxt[MX];
vi rgr[MX];

vi curCycle;
void dfs(int v) {
    if (cycle[v] != -1) {
        dbg(v);
        // we cycled
        curCycle.pb(v);
        cycle[v] = v;
        int i = 0;
        cycleRank[v] = i++;
        int cur = nxt[v];
        while (cur != v) {
            curCycle.pb(cur);
            cycle[cur] = v;
            cycleRank[cur] = i++;
            cur = nxt[cur];
        }
        cycleSize[v] = sz(curCycle);
        return;
    }
    cycle[v] = -2;
    dfs(nxt[v]);
}

int T = 0;
void dfsTree(int v, int h, int r) {
    dbg(v, h, r);
    if (cycle[v] == -1) cycle[v] = -2;
    height[v] = h;
    root[v] = r;
    tin[v] = T++;
    trav(u, rgr[v]) {
        if (cycle[u] >= 0) continue; // if its in a cycle, don't go to it;
        dfsTree(u, h+1, r);
    }
    tout[v] = T++;
}
int a[MX];

bool checkDist(int x, int y, int dist) {
    int rx = root[x];
    int ry = root[y];
    bool ok = (cycle[rx] == cycle[ry]); // same component
    if (x == rx && y == ry) {
        // both are in cycle nodes in same cycle
        int d = (cycleRank[y]-cycleRank[x]+cycleSize[cycle[x]])%cycleSize[cycle[x]];
        if (d > dist) ok = 0;
    } else if (x == rx && y != ry) ok = 0;
    else if (x != rx && y == ry) {
        int d = height[x];
        d += (cycleRank[y]-cycleRank[rx]+cycleSize[cycle[y]])%cycleSize[cycle[y]];
        if (d > dist) ok = 0;
    } else {
        if (rx != ry) ok = 0;
        else {
            if (tin[y] <= tin[x] && tout[y] >= tout[x]) { // y is an ancestor of x
                int d = height[x]-height[y];
                if (d > dist) ok = 0;
            } else ok = 0;
        }
    }
    return ok;
}
bool check(int dist) {
    int ptr = 0;
    F0R(i, n) {
        // see if we can get the ptr
        // we want to calculate the dist between i and ptr
        while (!checkDist(a[i], ptr, dist)) {
            ptr++;
            if (ptr == m) return 0;
        }
        dbg(i, a[i], ptr);
    }
    return 1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        F0R(i, m) {
            root[i] = -1;
            cycle[i] = -1;
            rgr[i].clear();
            nxt[i] = -1;
            height[i] = -1;
            cycleRank[i] = -1;
            tin[i] = tout[i] = -1;
            cycleSize[i] = -1;
        }
        F0R(i, n) {
            cin >> a[i]; a[i]--;
        }
        F0R(i, m) {
            int x; cin >> x;
            x--;
            nxt[i] = x;
            rgr[x].pb(i);
        }
        // find all root cycles,
        F0R(i, m) {
            if (cycle[i] != -1) continue;
            dbg(i);
            // dfs from i until we hit i
            curCycle.clear();
            dfs(i);
            // dfs in each tree to calculate heights
            dbg("cycle");
            trav(v, curCycle) {
                T = 0;
                dfsTree(v, 0, v);
            }
        }
        
        int lo = 0, hi = m+1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            // check if we can do it with mid
            if (check(mid)) hi = mid;
            else lo = mid+1;
        }
        if (lo == m+1) cout << -1 << nl;
        else cout << lo << nl;
    }
    return 0;
}
