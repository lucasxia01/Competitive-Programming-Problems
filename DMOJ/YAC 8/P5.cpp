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

#define nl endl
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

mt19937_64 rng(18293);

const int MX = 100+5;

int hi = 0, idx = -1;
vi gr[MX];
int par[MX];
void dfs(int v, int p, int d) {
    if (ckmax(hi, d)) idx = v;
    dbg(v, p, d);
    par[v] = p;
    trav(u, gr[v]) {
        if (u == p) continue;
        dfs(u, v, d+1);
    }
}

vi order(MX);
int val[MX];
int n;
void dfs2(int v, int p, bool fresh, int hi, int prev, bool root=0) {
    dbg("dfs2", v, p, fresh, hi);
    bool newfresh = 0;
    int newhi = 0;
    if (fresh || order[p] > hi) {
        val[v] = (100*(val[p]/100)+p-1);
        newhi = max(hi, prev);
    } else {
        newfresh = 1;
        if (root) val[v] = (100*(val[p]/100)+p-1);
        else val[v] = (100*(val[p]/100+1)+p-1);
    }
    trav(u, gr[v]) {
        if (u == p) continue;
        dfs2(u, v, newfresh, newhi, order[p]);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    std::iota(all(order), 1);
    shuffle(all(order), rng);

    int type; cin >> type;
    if (type == 1) {
        // find the diameter and then the midpoint
        int n; cin >> n;
        F0R(i, n-1) {
            int u, v; cin >> u >> v;
            gr[u].pb(v);
            gr[v].pb(u);
        }
        dfs(1, 0, 0);
        int b = idx;
        hi = 0;
        idx = -1;
        dfs(b, 0, 0);
        // now find something midway
        int root = idx;
        F0R(i, hi/2) {
            root = par[root];
        }
        dbg(root);
        // dfs from root and do stuff
        dfs2(root, root, 0, MX+1, 0, 1);

        FOR(i, 1, n) cout << val[i]+1 << " ";
        cout << nl; cout.flush();
    } else {
        int q; cin >> q;
        while (q--) {
            int ax, ay; cin >> ax >> ay; 
            if (ax == -1 && ay == -1) break;
            ax--; ay--;
            int p1 = ax%100 + 1;
            int p2 = ay%100 + 1;
            int d1 = ax/100;
            int d2 = ay/100;
            if (d1 < d2) cout << p2 << nl;
            else if (d1 > d2) cout << p1 << nl;
            else {
                if (order[p1] < order[p2]) cout << p2 << nl;
                else cout << p1 << nl;
            }
            cout.flush();
        }
    }
    return 0;
}
