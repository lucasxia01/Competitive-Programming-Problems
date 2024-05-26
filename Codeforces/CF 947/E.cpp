#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<ll, ll> pl;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define F0Rd(i, a) for (int i = (a) - 1; i >= 0; i--)
#define FORd(i, a, b) for (int i = (b); i >= (a); i--)
#define trav(a, x) for (auto &a : x)
#define rep(i, a, b) for (int i = a; i < (b); ++i)

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
const ll INF = (1 << 29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4 * atan((ld)1);

template <typename T>
bool ckmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template <typename T>
bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

/**** Credit to chatgpt 4.0 ****/

// Stream operator for std::pair
template <typename T1, typename T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &v)
{
    out << "(" << v.first << ", " << v.second << ")";
    return out;
}

// Trait to check if a type is iterable
template <typename T, typename = void>
struct is_iterable : false_type
{
};

template <typename T>
struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type
{
};

// Stream operator for iterable types excluding std::string
template <typename TT>
typename enable_if<is_iterable<TT>::value && !is_same<TT, string>::value, ostream &>::type
operator<<(ostream &out, const TT &c)
{
    out << "{ ";
    for (const auto &x : c)
        out << x << " ";
    out << "}";
    return out;
}

template <typename T>
ostream &operator<<(ostream &out, std::stack<T> container)
{
    std::vector<T> elements;
    while (!container.empty())
    {
        elements.push_back(container.top());
        container.pop();
    }
    std::reverse(elements.begin(), elements.end()); // Reverse to maintain order
    return out << elements;
}

template <typename T>
ostream &operator<<(ostream &out, std::queue<T> container)
{
    std::vector<T> elements;
    while (!container.empty())
    {
        elements.push_back(container.front());
        container.pop();
    }
    return out << elements;
}

// Helper function to print std::priority_queue
template <typename T, typename Container, typename Compare>
ostream &operator<<(ostream &out, std::priority_queue<T, Container, Compare> pq)
{
    out << "{";
    while (!pq.empty())
    {
        out << " " << pq.top();
        pq.pop();
    }
    out << " }";
    return out;
}

#ifdef DBG
void dbg_out() { cerr << endl; }

template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}

#define dbg(...) cerr << #__VA_ARGS__ << ":", dbg_out(__VA_ARGS__);
#define dbg_array(a, n)         \
    cerr << #a << ": { ";       \
    for (int i = 0; i < n; i++) \
        cerr << a[i] << " ";    \
    cerr << "}\n";
#else
#define dbg(...)
#define dbg_array(a, n)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 2e5 + 5;

template <class T>
struct RMQ
{
    vector<vector<T>> jmp;
    RMQ(const vector<T> &V) : jmp(1, V)
    {
        for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k)
        {
            jmp.emplace_back(sz(V) - pw * 2 + 1);
            rep(j, 0, sz(jmp[k]))
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
        }
    }
    T query(int a, int b)
    {
        assert(a < b); // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

struct LCA
{
    int T = 0;
    vi time, path, ret;
    RMQ<int> rmq;

    LCA(vector<vi> &C) : time(sz(C)), rmq((dfs(C, 0, -1), ret)) {}
    void dfs(vector<vi> &C, int v, int par)
    {
        time[v] = T++;
        for (int y : C[v])
            if (y != par)
            {
                path.push_back(v), ret.push_back(time[v]);
                dfs(C, y, v);
            }
    }

    int lca(int a, int b)
    {
        if (a == b)
            return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
    // dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

vi gr[MX];
int dep[MX];
int par[MX];
ll val[MX];
ll r[MX];
int tin[MX], tout[MX];
int T = 0;
void dfs(int v, int p, int d)
{
    tin[v] = T++;
    dbg(v, p, d);
    dep[v] = d;
    par[v] = p;
    val[v] = ((p == -1 ? 0LL : val[p]) ^ r[v]);
    for (int u : gr[v])
    {
        if (u == p)
            continue;
        dfs(u, v, d + 1);
    }
    tout[v] = T++;
}

bool is_ancestor(int u, int v) // if u is ancestor of v
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // somehow need to keep track of the 2 endpoints...
    int t;
    cin >> t;
    while (t--)
    {
        int n, q;
        cin >> n >> q;
        T = 0;
        F0R(i, n)
        {
            gr[i].clear();
            dep[i] = 0;
            par[i] = -1;
            val[i] = 0;
            tin[i] = tout[i] = 0;
        }
        // root it at 1
        int c[n];
        F0R(i, n)
        cin >> c[i];
        vector<vi> C(n);
        F0R(i, n - 1)
        {
            int u, v;
            cin >> u >> v;
            u--, v--;
            gr[u].pb(v);
            gr[v].pb(u);
            C[u].pb(v);
            C[v].pb(u);
        }
        LCA l(C);
        F0R(i, n)
        r[i] = rng() % (1LL << 60);
        // r[i] = (1 << i);
        dfs(0, -1, 0);
        // store the depths
        map<int, set<int>> depth_cnt;
        ll curVal = 0;
        F0R(i, n)
        if (c[i])
        {
            depth_cnt[dep[i]].insert(i);
            curVal ^= r[i];
        }
        // keep track of depths with at least 2
        set<int> depths_with_2;
        F0R(i, n)
        if (depth_cnt.count(i) && depth_cnt[i].size() >= 2)
            depths_with_2.insert(i);
        while (q--)
        {
            int x;
            cin >> x;
            x--; // the node to the toggled
            dbg("toggling", x + 1);
            if (c[x])
            { // toggle it off
                depth_cnt[dep[x]].erase(x);
                if (depth_cnt[dep[x]].empty())
                    depth_cnt.erase(dep[x]);
                else if (sz(depth_cnt[dep[x]]) == 1)
                {
                    depths_with_2.erase(dep[x]);
                }
            }
            else
            { // toggle it on
                if (depth_cnt.count(dep[x]) == 0)
                {
                    depth_cnt[dep[x]] = set<int>();
                }
                else if (sz(depth_cnt[dep[x]]) == 1)
                {
                    depths_with_2.insert(dep[x]);
                }
                depth_cnt[dep[x]].insert(x);
            }
            c[x] ^= 1;
            curVal ^= r[x];
            if (curVal == 0)
            {
                cout << "NO" << nl;
                continue;
            }
            // now do some casework
            // the lowest depth node
            trav(p, depth_cnt)
            {
                dbg(p.f, p.s);
            }
            dbg(depth_cnt.begin()->f);
            int lca = *((depth_cnt.begin()->s).begin());
            ll expVal;
            int a, b;
            if (sz(depths_with_2) == 0)
            {
                // take the min and max of the depths
                a = *(depth_cnt.begin()->s).begin();
                b = *(depth_cnt.rbegin()->s).begin();
            }
            else
            {
                // take max of depths and max with at least 2
                a = *(depth_cnt.rbegin()->s).begin();
                int highestDepth2 = *(depths_with_2.rbegin());
                auto it = depth_cnt[highestDepth2].begin();
                b = *it;
                if (is_ancestor(b, a))
                {
                    it++;
                    assert(it != depth_cnt[highestDepth2].end());
                    b = *it;
                    assert(!is_ancestor(b, a));
                }
            }
            // check that lca is actually the lca of a and b?
            if (l.lca(a, b) != lca)
            {
                cout << "NO" << endl;
                continue;
            }
            dbg("endpoints", a + 1, b + 1, "lca", lca + 1);
            expVal = (val[a] ^ val[b] ^ r[lca]);
            // dbg(val[a], val[b], r[lca], curVal, expVal);
            cout << (curVal == expVal ? "YES" : "NO") << endl;
        }
    }
    return 0;
}
