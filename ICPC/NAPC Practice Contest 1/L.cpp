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

struct Tree {
	typedef int T;
	static constexpr T unit = 0;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

static char buf[450 << 20];
void* operator new(size_t s) {
	static size_t i = sizeof buf;
	assert(s < i);
	return (void*)&buf[i -= s];
}
void operator delete(void*) {}

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mset = inf, madd = 0, val = -1;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

const int MX = 1<<20;

struct Seg {
    int d, a, b, c;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int h, w, n; cin >> h >> w >> n;
    string g[h];
    F0R(i, h) cin >> g[i];
    pi cur = {h-1, 0};
    vector<Seg> segs;
    vector<Tree> V, H;
    F0R(i, h) {
        Tree t(w);
        F0R(j, w) {
            int val = (g[i][j] == '.' ? 0 : 1);
            t.update(j, val);
        }
        H.pb(t);
    }
    F0R(i, w) {
        Tree t(h);
        F0R(j, h) {
            int val = (g[i][j] == '.' ? 0 : 1);
            t.update(j, val);
        }
        V.pb(t);
    }
    F0R(i, n) {
        string s; int x; cin >> s >> x;
        pi p = cur;
        int dir = 0;
        if (s == "up") cur.f -= x;
        else if (s == "right") { dir = 1; cur.s += x; }
        else if (s == "down") { dir = 2; cur.f += x; }
        else if (s == "left") { dir = 3; cur.s -= x; }
        pi q = cur;
        if (s == "up" || s == "down") {
            segs.pb({dir, cur.s, min(p.f, q.f), max(p.f, q.f)});
        } else {
            segs.pb({dir, cur.f, min(p.s, q.s), max(p.s, q.s)});
        }
    }
    int segNum = n;
    int time = 0;
    F0Rd(i, n) {
        Seg e = segs[i];
        if (e.d%2 == 0) { // vertical
            int ret = V[e.a].query(e.b, e.c);
            if (ret == 1) {
                segNum = i;
                if (e.d == 0) {
                    FOR(j, e.b, e.c) {
                        if (g[j][e.a] == '#') {
                            time = e.c-j+1;
                            break;
                        }
                    }
                } else {
                    FORd(j, e.b, e.c) {
                        if (g[j][e.a] == '#') {
                            time = j-e.b+1;
                            break;
                        }
                    }
                }
                break;
            }
        } else {
            int ret = H[e.a].query(e.b, e.c);
            if (ret == 1) {
                segNum = i;
                if (e.d == 3) {
                    FOR(j, e.b, e.c) {
                        if (g[e.a][j] == '#') {
                            time = e.c-j+1;
                            break;
                        }
                    }
                } else {
                    FORd(j, e.b, e.c) {
                        if (g[e.a][j] == '#') {
                            time = j-e.b+1;
                            break;
                        }
                    }
                }
                break;
            }
        }
        if (i == 0) segNum = -1; 
    }
    dbg(segNum, time);
    int fAns = time;
    F0R(i, segNum) {
        fAns += segs[i].c-segs[i].b;
    }
    cout << fAns << nl;

    // now we want to calc latest visit time to each cell
    vector<Node> LV, LH;
    F0R(i, w) {
        vi v(h, 0);
        Node t(v, -1, h);
        LV.pb(t);
    }
    F0R(i, h) {
        vi v(w, 0);
        Node t(v, -1, w);
        LH.pb(t);
    }
    F0R(i, n) {
        Seg e = segs[i];
        if (e.d%2 == 0) {
            LV[e.a].set(e.b, e.c, i);
        } else {
            LH[e.a].set(e.b, e.c, i);
        }
    }
    vpi pts;
    F0R(i, h) F0R(j, w) {
        LH[i].query()
    }
    return 0;
}
