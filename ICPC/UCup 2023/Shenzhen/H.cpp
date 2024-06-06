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

const int MX = 5e5+5;

bool vis[MX];
bool sources[MX];

vi val, comp, z, cont;
int Time, ncomps;
int n, m;
template<class G, class F> int dfs(int j, G& g, F& f) {
	int low = val[j] = ++Time, x; z.push_back(j);
	for (auto e : g[j]) if (comp[e.f] < 0)
		low = min(low, val[e.f] ?: dfs(e.f,g,f));

	if (low == val[j]) {
		do {
			x = z.back(); z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		} while (x != j);
		f(cont); cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
	val.assign(n, 0); comp.assign(n, -1);
	Time = ncomps = 0;
    z.clear();
    cont.clear();
	rep(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}

vpi gr[MX], rgr[MX]; // graph and reverse graph

bool seen[MX];
vi cur;
void dfs2(int v) {
    if (seen[v]) return;
    seen[v] = 1;
    trav(e, gr[v]) {
        cur.pb(e.s);
        dfs2(e.f);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> m;
        F0R(i, n) vis[i] = 0;
        F0R(i, n) sources[i] = 0; 
        F0R(i, n) seen[i] = 0;
        F0R(i, n) gr[i].clear();
        F0R(i, n) rgr[i].clear();
        vi start, end;
        vector<array<int, 4>> ops;
        F0R(i, m) {
            int l, x, r, y; cin >> l >> x >> r >> y;
            l--; x--; r--; y--;
            ops.pb({l, x, r, y});
            if (x&&y) {
                end.pb(i);
                sources[l] = sources[r] = 1;
            } else if (x&&!y) {
                gr[r].pb({l, i});
                rgr[l].pb({r, i});
            } else if (!x&&y) {
                gr[l].pb({r, i});
                rgr[r].pb({l, i});
            } else {
                start.pb(i);
            }
            vis[l] = vis[r] = 1;
        }
        int ans = 0;
        F0R(i, n) if (vis[i]) ans+=2;
        scc(gr, [&](vi& v) {
            if (!sz(v)) return;
            if (sz(v) == 1 && !vis[v[0]]) {
                return;
            }
            // dbg("size", sz(v), "comp label", comp[v[0]]);
            // dbg("comp", cont);
            // check if there's any sources in this component or if it has any parents
            bool ok = 0;
            trav(u, v) {
                trav(e, rgr[u]) {
                    if (comp[e.f] != comp[u]) {
                        // dbg(e.f);
                        ok = 1;
                    }
                }
                if (sources[u]) {
                    // dbg(u, sz(rgr[u]), sources[u]);
                    ok = 1;
                    break;
                }
            }
            // dbg(ok);
            if (!ok) {
                ans--;
                // pick someone random to be a source here
                sources[v[0]] = 1;
                // dbg("new source", v[0]);
            }
        });
        cout << ans << nl;
        // now we just compute the ordering by dfs-ing from every source and reversing the vector
        vi order = start;
        F0R(i, n) {
            if (seen[i] || !sources[i]) continue;
            cur.clear();
            dfs2(i);
            // dbg(i, cur);
            reverse(all(cur));
            order.insert(order.end(), cur.begin(), cur.end());
        }
        order.insert(order.end(), end.begin(), end.end());
        trav(o, order) cout << o+1 << " "; cout << nl;
        vi order_copy = order;
        sort(all(order_copy));
        vi V(m); iota(all(V), 0);
        if (V != order_copy) {
            while (1);
        }
        // // check this ordering now
        // int mark[n]; F0R(i, n) mark[i] = 0;
        // trav(o, order) {
        //     auto cur = ops[o];
        //     mark[cur[0]] = cur[1]+1;
        //     mark[cur[2]] = cur[3]+1;
        // }
        // // dbg_array(mark, n);
        // int ans2 = 0;
        // F0R(i, n) ans2 += mark[i];
        // dbg(ans, ans2);
        // assert(ans == ans2);
    }
    return 0;
}
