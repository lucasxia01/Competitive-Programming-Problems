// Jacob Zhang Boilerplate 2.3.0
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define FOR(i,a,b) for(int i = a; i < b; i++)
#define ROF(i,a,b) for(int i = b-1; i >= a; i--)

// overloaded << operator for printing vectors. Idea from Neal Wu
template<typename T> ostream& operator<< (ostream& os, vector<T> v) {
    os << '['; string sep; for (const T& el : v) os << sep << el, sep = ", "; return os << ']';
}
// overloaded << operator for printing pairs
template<typename S, typename T> ostream& operator<< (ostream& os, pair<S,T> p) {
    return os << '(' << p.first << "," << p.second << ")";
} 
// cool recursive template for debug printing. also Neal Wu
void dbg_out () {cerr << endl;}
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) {
    cerr << ' ' << H; dbg_out(T...);
}


#ifdef JACOB_DEBUG
#define dbg(desc, ...) cerr << '(' << desc << "):"; dbg_out(__VA_ARGS__);
#define dbg_args(...) dbg(#__VA_ARGS__, __VA_ARGS__)
#else
#define dbg(...)
#define dbg_args(...)
#endif

// KACTL defines
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

int L, V, R; 
    int SOURCE = 0;
    int SINK = 1;
map<string, int> word_to_vertex;
vector<string> vertex_to_word(2);
vector<vi> adjlist;
vector<int> loc_vertex;
int n;

string print_itinerary(Dinic& d) {
    stringstream s;
    int num_locs_visited = 0;
    int num_colors = 0;
    for(Dinic::Edge& e : d.adj[SOURCE]) {
        int num_from_here = e.flow();
        if (num_from_here == 0) continue;
        num_colors += num_from_here;
        num_locs_visited++;
        int loc_num = e.to;
        s << vertex_to_word[loc_num] << ' ' << num_from_here;
        for(Dinic::Edge& e_to_color : d.adj[loc_num]) {
            if (e_to_color.flow()) {
                s << ' ' << vertex_to_word[e_to_color.to];
            }
        }
        s << '\n';
    }
    return to_string(num_colors) + " " + to_string(num_locs_visited) + "\n" + s.str();
}

 
void run () {
    cin >> L >> V >> R;
    dbg_args(L,V,R);

    int ctr = 2;
    auto add_word = [&](const string& s) -> void {
        if (word_to_vertex[s]) return;
        word_to_vertex[s] = ctr;
        vertex_to_word.push_back(s);
        ctr++;
    };

    adjlist.resize(L);
    loc_vertex.resize(L);
    FOR(i,0,L) {
        string loc_name; cin>> loc_name;
        add_word(loc_name);
        loc_vertex[i] = word_to_vertex[loc_name];
        int k; cin >> k;
        FOR(j,0,k) {
            string color; cin >> color;
            add_word(color);
            adjlist[i].push_back(word_to_vertex[color]);
        }
    }

    n = ctr;
    int best_num_colors = 0;
    string best_itin = "oops";

    FOR(mask,0,1 << L) {
        if (__builtin_popcount(mask) != V) continue;
        Dinic d(n);
        vector<bool> already_added_color(n);
        FOR(i,0,L) {
            d.addEdge(SOURCE, loc_vertex[i], R * ((mask >> i) & 1));
            for (int color_vtx : adjlist[i]) {
                d.addEdge(loc_vertex[i], color_vtx, 1);
                if (!already_added_color[color_vtx]) {
                    d.addEdge(color_vtx, SINK, 1);
                    already_added_color[color_vtx] = true;
                }
            }
        }
        int num_colors = d.calc(SOURCE, SINK);
        if (num_colors > best_num_colors) {
            best_num_colors = num_colors;
            best_itin = print_itinerary(d);
        }
    }
    cout << best_itin;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    run();
}
