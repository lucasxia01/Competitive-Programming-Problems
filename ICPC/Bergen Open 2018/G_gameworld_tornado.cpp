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

const int inf = 1e9;
const ll MX = inf+100;

struct E {
    int x, y1, y2, s;
    bool operator<(const E& o) const {
        return tie(x, s, y1, y2) < tie(o.x, o.s, o.y1, o.y2);
    }
};

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, madd = 0, val = 0, cnt = hi-lo;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of 0
	int query(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return (val==0?cnt:0);
		push();
		return l->query(L, R) + r->query(L, R);
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
            if (l->val < r->val) cnt = l->cnt;
            else if (l->val > r->val) cnt = r->cnt;
            else cnt = l->cnt + r->cnt;
			val = min(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

Node st(0, MX);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<E> v;
    F0R(i, n) {
        int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
        v.pb({x1, y1, y2, 1});
        v.pb({x2, y1, y2, 0});
    }
    sort(all(v));
    int prevx = -1;
    ll ans = 0;
    trav(e, v) {
        // dbg(e.x, e.y1, e.y2, e.s, MX-st.query(0, MX));
        if (prevx == -1) prevx = e.x;
        ans += ((ll)MX-st.query(0, MX))*(e.x - prevx);
        if (e.s == 0) st.add(e.y1, e.y2, -1);
        else st.add(e.y1, e.y2, 1);
        prevx = e.x;
    }
    cout << ans << nl;
    return 0;
}
