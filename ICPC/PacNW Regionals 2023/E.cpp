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

const int MX = 500+5;

vi gr[MX];
set<pi> edges;
vi ans;

// I need a function that computes the lower bound on the remaining graph given some start vertex


void dfs(const set<int>& cur_nodes, int v, int p, set<int>& comp) {
    comp.insert(v);
    trav(u, gr[v]) {
        if (!cur_nodes.count(u)) continue;
        dfs(u, v);
    }
}

void solve(set<int> cur_nodes, int root, int target) {    
    // try splitting at every point
    trav(v, cur_nodes) {
        // split at v
        trav(u, gr[v]) {
            if (!cur_nodes.count(u)) continue;
            set<int> comp;
            dfs(cur_nodes, u, v, comp);
            // find how many leaves are in this component
            map<int, int> deg_cnt;
            trav(w, comp) {
                deg_cnt[w] = 0;
                trav(l, gr[w]) {
                    if (!comp.count(l)) continue;
                    deg_cnt[w]++;
                }
            }
            int leaves = 0;
            trav(w, comp) {
                if (deg_cnt[w] == 1) leaves++;
            }
            // the possible range is [leaves-2, sz(comp)-1]
            // if this remaining thing is a tree rooted at u, then we could have a problem...

            // otherwise, 
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    F0R(i, n-1) {
        int a, b; cin >> a >> b;
        gr[a].pb(b);
        gr[b].pb(a);
        edges.insert({a, b});
        edges.insert({b, a});
    }
    // check if its possible in the first place
    int leaves = 0;
    FOR(i, 1, n) if (sz(gr[i]) == 1) leaves++;
    bool ok = 1;
    if (n == 1) ok = 1;
    else if (n == 2) {
        if (k == 1) ok = 0;
    } else if (leaves == n-1) {
        if (k == n-1 || k < leaves-2) ok = 0;
    } else {
        if (k < leaves-2) ok = 0;
    }
    if (!ok) {
        cout << -1 << nl;
        return 0;
    }
    // see what we can do
    set<int> all; FOR(i, 1, n) all.insert(i);
    solve(all, k);
    return 0;
}
