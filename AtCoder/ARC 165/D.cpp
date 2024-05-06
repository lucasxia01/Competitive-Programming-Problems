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
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
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

void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << H << " ";
    dbg_out(T...);
}

#ifdef DBG
#define dbg(...) dbg_out(__VA_ARGS__);
template <typename T1, typename T2>
ostream &operator<<(ostream &c, pair<T1, T2> &v)
{
    c << "(" << v.fi << "," << v.se << ")";
    return c;
}

template <template <class...> class TT, class... T>
ostream &operator<<(ostream &out, TT<T...> &c)
{
    out << "{ ";
    trav(x, c) out << x << " ";
    out << "}";
    return out;
}
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 2000 + 5;

struct Edge
{
    int a, b, c, d, i;
};

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

vector<Edge> gr[MX];

vector<Edge> curCycle;
bool been[MX];
bool dfs(int v, int start, bool first=0) {
    dbg(v, start, first);
    if (!first && v == start) return 1;
    if (been[v]) return 0;
    been[v] = 1;
    trav(e, gr[v]) {
        if (dfs(e.c, start)) {
            curCycle.pb(e);
            return 1;
        }
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    bool end = 0;
    F0R(i, m) {
        cin >> edges[i].a >> edges[i].b >> edges[i].c >> edges[i].d;
        if (edges[i].a == edges[i].c) {
            if (edges[i].c >= edges[i].d) end = 1;
            else edges[i].a = -1;
        }
        edges[i].i = i;
    }
    if (end) {
        cout << -1 << nl;
        return 0;
    }
    UF uf(n+1);
    while (1) {
        // top sort until contradiction or no cycles
        bool vis[n+1]; 
        int degCnt[n+1]; 
        F0R(i, n+1) degCnt[i] = 0;
        F0R(i, n+1) vis[i] = 1;
        F0R(i, n+1) gr[i].clear();
        F0R(i, n+1) been[i] = 0;

        F0R(i, m) {
            if (edges[i].a == -1) continue;
            vis[edges[i].a] = vis[edges[i].c] = 0;
            gr[edges[i].a].pb(edges[i]);
            degCnt[edges[i].c]++;
        };
        queue<int> q;
        FOR(i, 1, n) {
            if (degCnt[i] == 0) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            vis[cur] = 1;
            trav(e, gr[cur]) {
                degCnt[e.c]--;
                if (degCnt[e.c] == 0) {
                    q.push(e.c);
                }
            }
        }
        bool isCycle = 0;
        // see if there's anything left
        bool ok = 1;
        FOR(i, 1, n) if (vis[i] == 0) {
            curCycle.clear();
            dbg(i);
            // find the cycle and delete an edge and update all of the edges in this cycle
            if (!dfs(i, i, 1)) continue;
            isCycle = 1;
            int lo = INF;
            trav(e, curCycle) {
                // find the lowest one and then update!
                if (e.b-e.a < e.d-e.c) ckmin(lo, e.b-e.a+1);
            }
            if (lo == INF) {
                ok = 0;
                break;
            }
            lo = 1;
            dbg(lo);
            F0R(j, lo) {
                trav(e, curCycle) {
                    dbg("join", e.a+j, e.c+j);
                    uf.join(e.a+j, e.c+j);
                }
            }
            dbg("passed", i, sz(curCycle), lo);
            trav(f, edges) { // need to update everything with this start
                if (f.a == -1) continue;
                // update it
                dbg(f.a, f.c);
                while (f.a <= n && f.c <= n && uf.sameSet(f.a, f.c)) {
                    f.a++;
                    f.c++;
                }
                dbg(f.a, f.c);
                if (f.c > f.d) ok = 0;
                if (f.a > f.b) f.a = -1;
            }
            break;
        }
        if (!ok) {
            cout << "No" << nl;
            break;
        } else if (!isCycle) {
            cout << "Yes" << nl;
            break;
        }
    }
    return 0;
}
