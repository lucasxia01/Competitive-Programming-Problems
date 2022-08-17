#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <chrono>
#include <cassert>
#include <climits>

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

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			F0R(j,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	int T = 0;
	vi time, path, ret, depth, p;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1,0), ret)), depth(sz(C)), p(sz(C)) {}
	void dfs(vector<vi>& C, int v, int par, int d) {
        p[v] = par;
		time[v] = T++;
        depth[v] = d;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v, d+1);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	int dist(int a, int b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

vector<vi> gr;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    F0R(tt, t) {
        int n; cin >> n;
        gr.clear();
        F0R(i, n) {
            vi temp; gr.pb(temp);
        }
        F0R(i, n-1) {
            int a, b; cin >> a >> b;
            a--; b--;
            gr[a].pb(b);
            gr[b].pb(a);
        }
        vi f[n];
        F0R(i, n) {
            int x; cin >> x; x--;
            f[x].pb(i);
        }
        bool mark[n]; F0R(i, n) mark[i] = 0;
        LCA l(gr);
        int ans = n-1;
        vpi V;
        F0R(i, n) {
            if (!sz(f[i])) continue;
            // find the lca of everything
            int cur = -1;
            trav(ff, f[i]) {
                if (cur == -1) cur = ff;
                else cur = l.lca(cur, ff);
            }
            V.pb({l.depth[cur], i});
        }
        sort(all(V));
        trav(u, V) {
            int i = u.s;
            assert(sz(f[i]));
            // now we want to trace a path from ff to cur
            trav(ff, f[i]) {
                // follow the parents
                int v = ff;
                while (!mark[v] && l.depth[v] > u.f) {
                    mark[v] = 1;
                    v = l.p[v];
                    ans--;
                }
            }
        }
        cout << "Case #" << tt+1 << ": " << ans << nl;
    }
    return 0;
}
