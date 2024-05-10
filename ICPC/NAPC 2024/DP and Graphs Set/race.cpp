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

const int MX = 2e5+5;

int n, k;
vpi adj[MX];
vector<bool> dead(MX, 0);
int subtree_size[MX];

int get_subtree_size(int node, int parent = -1) {
    if (dead[node]) {
        subtree_size[node] = 0;
        return 0;
    }
	int &res = subtree_size[node];
	res = 1;
	for (pi i : adj[node]) {
		if (i.f == parent) { continue; }
		res += get_subtree_size(i.f, node);
	}
	return res;
}

int get_centroid(int node, int start, int parent = -1) {
    // if (dead[node]) assert(0);
	for (pi i : adj[node]) {
		if (i.f == parent) { continue; }

		if (subtree_size[i.f] * 2 > subtree_size[start]) { return get_centroid(i.f, start, node); }
	}
	return node;
}

array<int, 3> dist[MX]; // dist, length, child root
vi comp;
const int maxK = 1e6+5;
void calc_dist(int node, int depth, int par, int d, int root = -1) {
    dbg("calc_dist", node, depth, par, d, root, dead[node]);
    if (dead[node]) return;
    if (d > k) return;
    comp.pb(node);
    dist[node] = {d, depth, root};
    trav(u, adj[node]) {
        if (u.f == par) continue;
        int newRoot = root;
        if (root == -1) newRoot = u.f;
        calc_dist(u.f, depth+1, node, d+u.s, newRoot);
    }
}

int ans = MX;
vpi cnt[maxK];  // map from dist to pair of depth, childNode
void solve(int node) {
    if (dead[node]) return;
    get_subtree_size(node);
    int cent = get_centroid(node, node);
    dbg(node, cent);
    // dfs on cent and store all the lengths
    comp.clear();
    calc_dist(cent, 0, -1, 0);
    dbg(comp);
    // now two sum the component
    trav(v, comp) {
        int d = dist[v][0];
        cnt[d].clear();
        cnt[k-d].clear();
    }
    set<int> dists;
    trav(v, comp) {
        if (v == cent) continue;
        dbg(dist[v][0], dist[v][1], dist[v][2]);
        cnt[dist[v][0]].pb({dist[v][1], dist[v][2]});
        dists.insert(dist[v][0]);
    }
    trav(d, dists) {
        vpi tmp = {{MX, -1}, {MX, -1}}; // best and second best options
        // find the first two not from the same childNode
        trav(x, cnt[d]) {
            bool match = 0;
            F0R(i, 2) {
                if (tmp[i].s == x.s) {
                    ckmin(tmp[i].f, x.f);
                    match = 1;
                    break;
                }
            }
            if (!match) {
                // see if its better than best
                if (x.f < tmp[0].f) {
                    tmp[1] = tmp[0];
                    tmp[0] = x;
                } else if (x.f < tmp[1].f) {
                    tmp[1] = x;
                }
            }
            if (tmp[0].f > tmp[1].f) swap(tmp[0], tmp[1]);
        }
        if (tmp[1].s == -1) tmp.pop_back();
        cnt[d] = tmp;
        dbg(d, cnt[d]);
    }
    // now two sum on this
    trav(d, dists) {
        if (d == k) {
            // assert(sz(cnt[d]) > 0);
            ckmin(ans, cnt[d][0].f);
        }
        int rem = k-d;
        if (rem < 0) continue;
        if (!sz(cnt[rem])) continue;
        trav(x, cnt[d]) {
            trav(y, cnt[rem]) {
                if (x.s != y.s) {
                    ckmin(ans, x.f+y.f);
                }
            }
        }
    }
    dbg("marking dead", cent);
    dead[cent] = 1;
    trav(u, adj[cent]) {
        solve(u.f);
    }
}

int best_path(int N, int K, int H[][2], int L[]) {
    n = N;
    k = K;
    F0R(i, N-1) {
        adj[H[i][0]].pb({H[i][1], L[i]});
        adj[H[i][1]].pb({H[i][0], L[i]});
    }
    solve(0);
    if (ans == MX) return -1;
    return ans;
}

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(0); cout.tie(0);
//     int n, k; cin >> n >> k;
//     int H[n-1][2]; F0R(i, n-1) cin >> H[i][0] >> H[i][1];
//     int L[n-1]; F0R(i, n-1) cin >> L[i];
//     cout << best_path(n, k, H, L) << nl;
//     return 0;
// }
