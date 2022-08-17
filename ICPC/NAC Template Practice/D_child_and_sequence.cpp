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

#define int long long

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

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(...) dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;
const int inf = 1e9;

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mset = inf, val = -inf, sum = 0;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
            sum = l->sum + r->sum;
		}
		else {
            val = v[lo];
            sum = v[lo];
        }
	}
	pi query(int L, int R) {
		if (R <= lo || hi <= L) return {-inf, 0};
		if (L <= lo && hi <= R) {
            // dbg(lo, hi, sum);
            return {val, sum};
        }
		push();
        pi a = l->query(L, R);
        pi b = r->query(L, R);
		return {max(a.f, b.f), a.s+b.s};
	}
    void mod(int L, int R, int x, Node* tr) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R && val < x) return;
        else if (L <= lo && hi <= R && lo+1==hi) {
            // dbg("SETTING ", lo, val, val%x);
            tr->set(lo, hi, val%x);
        }
		push();
        l->mod(L, R, x, tr);
        r->mod(L, R, x, tr);
		return;
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = sum = x;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
            sum = l->sum + r->sum;
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
	}
};
Node* tr;


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vi a(n); F0R(i, n) cin >> a[i];
    tr = new Node(a, 0, n);
    F0R(i, m) {
        int t; cin >> t;
        int l, r, x;
        if (t == 1) {
            cin >> l >> r;
            cout << tr->query(l-1, r).s << nl;
        } else if (t == 2) {
            cin >> l >> r >> x;
            tr->mod(l-1, r, x, tr);
            // F0R(i, n) {
            //     cout << tr->query(i, i+1)
            // }
        } else {
            cin >> l >> x;
            tr->set(l-1, l, x);
        }
    }
}
