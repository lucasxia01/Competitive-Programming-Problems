#include <bits/stdc++.h>
//#include <bits/extc++.h>
//using namespace __gnu_pbds;
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define repb(i, a, b) for(int i = (a); i >= (b); --i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define ff first
#define ss second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define pb push_back

#define ln '\n'
template<typename T1,typename T2>
ostream& operator <<(ostream& c,pair<T1,T2> &v){
	c<<"("<<v.ff<<","<<v.ss<<")"; return c;
}
template <template <class...> class TT, class ...T>
ostream& operator<<(ostream& out,TT<T...>& c){
    out<<"{ ";
    for(auto &x : c) out<<x<<" ";
    out<<"}"; return out;
}

const int MOD = 1e9+7, LIM = 3e5+5;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct SuffixArray {
	vi sa,lcp, rank;
	SuffixArray(string& s,int lim=256) {
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)+1),y(n), ws(max(n, lim));
		rank = y;
		sa = lcp = y, iota(all(sa),0);
		for (int j = 0,p = 0; p < n;j = max(1, j*2), lim=p) {
			p = j,iota(all(y),n-j);
			rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i]-j;
			fill(all(ws), 0);
			rep(i, 0, n) ws[x[i]]++;
			rep(i, 1, lim) ws[i] += ws[i-1];
			for(int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1, n) a = sa[i-1],b = sa[i], x[b] = 
					(y[a] == y[b] && y[a+j] == y[b+j])?p-1:p++;
		}
		rep(i, 1, n) rank[sa[i]] = i;
		for (int i = 0, j; i < n-1; lcp[rank[i++]] = k)
			for(k && k--, j = sa[rank[i] - 1];
				s[i+k] == s[j+k]; k++);
	}
};

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k=1; pw*2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw*2 + 1);
			rep(j, 0, sz(jmp[k]))
				jmp[k][j] = min(jmp[k-1][j], jmp[k-1][j+pw]);
		}
	}
	T query(int a, int b) { // [a, b)
		assert(a < b);
		int dep = 31 - __builtin_clz(b-a);
		return min(jmp[dep][a], jmp[dep][b-(1<<dep)]);
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	int tests = 1;
	// cin >> tests;

	while(tests--){
		string s; cin >> s;
		int n = sz(s);
		SuffixArray sa(s);
		// rep(i,0,n+1) cout << sa.sa[i] << " "; cout << ln;
		// rep(i,0,n+1) cout << sa.lcp[i] << " "; cout << ln;
		RMQ<int> rmq(sa.lcp);
		vector<pii> q; q.push_back({0, 0});
		int cur = 0; cout << "1 1" << ln;
		rep(i, 1, n) {
			// cout << i << ',' << sa.rank[i] << ln;
			while (sa.rank[i] > sa.rank[q.back().ff]) {
				int tmp = i + rmq.query(sa.rank[q.back().ff]+1, sa.rank[i]+1);
				if (q.back().ss >= tmp) q.pop_back();
				else {
					q.push_back({i, tmp});
					break;
				}
			}
			if (sz(q) > cur+1 && q[cur+1].ss == i) {
				cur++;
			}
			cout << q[cur].ff+1 << " " << i+1 << ln;
		}
	}
	return 0;
}
