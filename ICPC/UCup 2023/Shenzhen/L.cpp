#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(v) v.begin(), v.end()
#define sz(v) (int)v.size()
#define sq(a) ((a)*(a))

#define per(i,a,b) for (int i = (b)-1; i >= a; i--)
#define rep(i,a,b) for (int i=a; i<b; i++)

#define FOR(i,a,b) for (int i=a; i<b; i++)
#define F0R(i,a) for (int i=0; i<a; i++)
#define ROF(i,a,b) for (int i = (b)-1; i >= a; i--)
#define R0F(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);
#define finish(x) return cout << x << endl, 0;
#define dbg(x) cerr << ">>> " << #x << " = " << x << endl;
#define _ << " _ " <<

#define ll long long

template<class T> bool ckmin(T&a, T&b) { bool B = a > b; a = min(a,b); return B; }
template<class T> bool ckmax(T&a, T&b) { bool B = a < b; a = max(a,b); return B; }

typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ld,ld> pld;
typedef complex<ld> cd;

typedef vector<int> vi;
typedef vector<ld> vld;
typedef vector<vector<int>> vvi;

const ld PI = acos(-1.0);
const ld EPS = 1e-7;
const int MOD = 998244353;


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

void solve() {
  int n, m;
  cin >> n >> m;

  if (m == 0) {
    cout << (n - 1) << '\n';
    return;
  }

  vector<array<int, 3>> edges;

  vi u(m), v(m), w(m);
  set<int> imp;
  F0R(i, m){
    cin >> u[i] >> v[i] >> w[i];
    imp.insert(u[i]);
    imp.insert(v[i]);
  }

  vi il;
  int z = 0;
  map<int, int> rev;
  for (auto uv : imp){
    il.pb(uv);
    rev[uv] = z;
    z += 1;
  }

  assert (z);

  ll out = n - z;

  vi deg(z);
  F0R(i, m){
    deg[rev[u[i]]] += 1;
    deg[rev[v[i]]] += 1;

    edges.pb({w[i], rev[u[i]], rev[v[i]]});
  }

  F0R(i, z){
    int sz = 2 + 2 * deg[i];
    FOR(j, i - sz, i + sz + 1){
      if (j < 0 || j >= z) continue;

      edges.pb({abs(rev[i] - rev[j]), i, j});
    }
  }

  UF uf(z);

  for (auto [w, u, v] : edges){
    if (uf.join(u, v)){
      out += w;
    }
  }

  cout << out << '\n';
}

int32_t main() { FAST
  int t;
  cin >> t;

  while (t--){
    solve();
  }

  return 0;
}