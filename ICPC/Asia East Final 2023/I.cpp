#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define trav(a, x) for (auto& a: x)
#define f first
#define s second
#define pb push_back
const char nl = '\n';

#ifdef DBG
void dbg_out() { cerr << nl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e5+5;
int par[MX];
int SZ[MX];

int find(int x) {
    return (x==par[x]?x:par[x]=find(par[x]));
}
void merge(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;
    if (SZ[a] < SZ[b]) swap(a, b);
    SZ[a] += SZ[b];
    par[b] = a;
    SZ[b] = 0;
}
vi gr[MX];
vector<pii> edges;

vi num, st;
vector<vector<pii>> ed;
int Time;
vector<pii> bridge_edges;
template<class F>
int dfs(int at, int par, F& f) {
	int me = num[at] = ++Time, e, y, top = me;
	for (auto pa : ed[at]) if (pa.second != par) {
		tie(y, e) = pa;
		if (num[y]) {
			top = min(top, num[y]);
			if (num[y] < me)
				st.push_back(e);
		} else {
			int si = sz(st);
			int up = dfs(y, e, f);
			top = min(top, up);
			if (up == me) {
				st.push_back(e);
				f(vi(st.begin() + si, st.end()));
				st.resize(si);
			}
			else if (up < me) st.push_back(e);
			else { /* e is a bridge */ 
                bridge_edges.pb({edges[e].f, edges[e].s});
            }
		}
	}
	return top;
}

template<class F>
void bicomps(F f) {
	num.assign(sz(ed), 0);
	rep(i,0,sz(ed)) if (!num[i]) dfs(i, -1, f);
}
// template <class F>
// int dfs(int at, int par, F& f) {
//     int me = num[at] = ++Time, e, y, top=me;
//     for (auto pa : ed[at]) if (pa.second != par) {
//         tie(y, e) = pa;
//         if (num[y]) {
//             top = min(top, num[y]);
//             if (num[y] < me) {
//                 st.pb(e);
//             }
//         } else {
//             int si = sz(st);
//             int up = dfs(y, e, f);
//             top = min(top, up);
//             if (up == me) {
//                 st.pb(e);
//                 f(vi(st.begin()+si, st.end()));
//                 st.resize(si);
//             }
//             else if (up < me) st.pb(e);
//             else {
//                 // e is a bridge
//                 // create an edge in the graph
//                 bridge_edges.pb({edges[e].f, edges[e].s});
//             }
//         }
//     }
//     return top;
// }
// template <class F>
// void bicomps(F f) {
//     num.assign(sz(ed), 0);
//     rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1, f);
// }

struct Info {
    int subtreeSize = 0;
    int downLen = 0;
    int downCh = -1;
    int upLen = 0;
    int upCh = -1;
};

Info infos[MX];
bool good[MX];
int n, m;

int best = -1;
int root, upNode, downNode;

void solve(int v, int p) {
    infos[v].subtreeSize = SZ[find(v)];
    vector<pii> ups;
    vector<pii> downs;
    trav(u, gr[v]) {
        int node = find(u);
        if (node == p) continue;
        solve(node, v);
        // check if this is a good break edge going either up or down
        int valUp = infos[node].upLen;
        int valDown = infos[node].downLen;
        if (good[infos[node].subtreeSize]) {
            // then we can add to 1 this
            valUp++;
        }
        if (good[n-infos[node].subtreeSize]) {
            valDown++;
        }
        ups.pb({valUp, node});
        downs.pb({valDown, node});
        infos[v].subtreeSize += infos[node].subtreeSize;
    }
    {
        int len = 0;
        if (len > best) {
            best = len;
            root = v;
            upNode = downNode = -1;
        }
    }
    if (sz(ups) == 0) return;
    // find highest two
    sort(all(ups));
    reverse(all(ups));
    sort(all(downs));
    reverse(all(downs));
    // first just set the vals of v
    infos[v].upLen = ups[0].f;
    infos[v].upCh = ups[0].s;
    infos[v].downLen = downs[0].f;
    infos[v].downCh = downs[0].s;
    dbg("for node v", v);
    dbg("subtreeSize", infos[v].subtreeSize);
    dbg("upLen and upCh", infos[v].upLen, infos[v].upCh);
    dbg("downLen and downCh", infos[v].downLen, infos[v].downCh);
    {
        int len = ups[0].f;
        if (len > best) {
            best = len;
            root = v;
            upNode = ups[0].s;
            downNode = -1;
        }

        len = downs[0].f;
        if (len > best) {
            best = len;
            root = v;
            upNode = -1;
            downNode = downs[0].s;
        }
    }
    if (sz(ups) == 1) return;
    // merge the best up and best down as long as they're not the same child
    // try best up and best down
    // also just try best up and nothing and best down and nothing
    
    if (ups[0].s != downs[0].s) {
        int len = ups[0].f + downs[0].f;
        if (len > best) {
            best = len;
            root = v;
            upNode = ups[0].s;
            downNode = downs[0].s;
        }
    }
    if (ups[0].s != downs[1].s) {
        int len = ups[0].f + downs[1].f;
        if (len > best) {
            best = len;
            root = v;
            upNode = ups[0].s;
            downNode = downs[1].s;
        }
    }
    if (ups[1].s != downs[0].s) {
        int len = ups[1].f + downs[0].f;
        if (len > best) {
            best = len;
            root = v;
            upNode = ups[1].s;
            downNode = downs[0].s;
        }
    }
    
}

int vis[MX];
void mark(int v, int x, int nxt) {
    if (v == nxt) return; // don't cross into next section
    if (vis[v]) return;
    vis[v] = x;
    trav(u, gr[v]) {
        mark(u, x, nxt);
    }
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t; 
    cin >> t;
    // t = 1;
    while (t--) {
        bridge_edges.clear();
        bridge_edges.shrink_to_fit();
        best = -1;
        root = upNode = downNode = -1;
        cin >> n >> m;
        // n = 1e4, m = 1e4-1;
        // reset everything
        rep(i, 0, n) {
            par[i] = i;
            SZ[i] = 1;
        }
        rep(i, 0, n) {
            infos[i] = Info();
        }
        rep(i, 0, n) vis[i] = 0;
        rep(i, 0, n) {
            gr[i].clear();
            gr[i].shrink_to_fit();
        }
        edges.clear();
        edges.shrink_to_fit();
        int eid = 0; 
        ed.clear();
        ed.shrink_to_fit();
        ed.resize(n);
        Time = 0;
        num.clear();
        num.shrink_to_fit();
        st.clear();
        st.shrink_to_fit();
        rep(i, 0, m) {
            int u, v; 
            cin >> u >> v;
            // u = i+1, v = i+2;
            u--; v--;
            edges.pb({u, v});
            ed[u].emplace_back(v, eid);
            ed[v].emplace_back(u, eid++);
        }
        bicomps([&](const vi& edgelist) {
            // merge the whole component togther
            trav(e, edgelist) {
                merge(edges[e].f, edges[e].s);
            }
        });
        // actually add the bridge edges now
        trav(p, bridge_edges) {
            dbg("bridge", find(p.f), find(p.s));
            gr[find(p.f)].pb(find(p.s));
            gr[find(p.s)].pb(find(p.f));
        }
        int freq[n+1]; rep(i, 0, n+1) freq[i] = 0;
        rep(i, 0, n) {
            int x; 
            cin >> x;
            // x = 1;
            freq[x]++;
        }
        vector<pii> sizes;
        rep(i, 1, n+1) {
            if (freq[i]) sizes.pb({i, freq[i]});
        }
        // find all the good breaks
        rep(i, 0, n) good[i] = 0;
        int cur = 0;
        trav(p, sizes) {
            dbg(p.f, p.s);
            cur += p.s;
            if (cur != n) good[cur] = 1;
        }
        assert(cur == n);

        // now dfs from random root
        solve(find(0), -1);
        int d = sz(sizes);
        dbg("d", d);
        dbg("best len", best);
        dbg("root, upNode, downNode", root, upNode, downNode);
        if (best != d-1) {
            cout << "No" << nl;
            continue;
        }
        cout << "Yes" << nl;
        // we have a path with d-1 breaks in it
        // this path is stored in root, upNode, downNode
        vi path;
        while (upNode != -1) {
            path.pb(upNode);
            upNode = infos[upNode].upCh;
        }
        reverse(all(path));
        path.pb(root);
        while (downNode != -1) {
            path.pb(downNode);
            downNode = infos[downNode].downCh;
        }

        // trav(v, path) cerr << v << ' '; cerr << nl;
        bool beforeRoot = 1;
        int dcnt = 0;
        rep(i, 0, sz(path)) {
            if (path[i] == root) beforeRoot = 0;
            if (beforeRoot && !good[infos[path[i]].subtreeSize]) continue;
            else if (!beforeRoot) {
                if (i != sz(path)-1 && !good[n-infos[path[i+1]].subtreeSize]) {
                    continue;
                }
            }
            int nxt = -1;
            // check if this is actually a good break
            if (i != sz(path)-1) nxt = path[i+1];
            mark(path[i], sizes[dcnt++].f, nxt);
        }
        rep(i, 0, n) {
            cout << vis[find(i)] << " ";
        }
        cout << nl;
    }

}