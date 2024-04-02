#pragma -fsanitize=address
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
#define int ll

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

/**** Credit to chatgpt 4.0 ****/

// Stream operator for std::pair
template<typename T1, typename T2>
ostream& operator<<(ostream &out, const pair<T1, T2> &v) {
    out << "(" << v.first << ", " << v.second << ")"; 
    return out;
}

// Trait to check if a type is iterable
template<typename T, typename = void>
struct is_iterable : false_type {};

template<typename T>
struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type {};

// Stream operator for iterable types excluding std::string
template<typename TT>
typename enable_if<is_iterable<TT>::value && !is_same<TT, string>::value, ostream&>::type
operator<<(ostream& out, const TT& c) {
    out << "{ ";
    for (const auto& x : c) out << x << " ";
    out << "}"; 
    return out;
}

template<typename T>
ostream& operator<<(ostream& out, std::stack<T> container) {
    std::vector<T> elements;
    while (!container.empty()) {
        elements.push_back(container.top());
        container.pop();
    }
    std::reverse(elements.begin(), elements.end()); // Reverse to maintain order
    return out << elements;
}

template<typename T>
ostream& operator<<(ostream& out, std::queue<T> container) {
    std::vector<T> elements;
    while (!container.empty()) {
        elements.push_back(container.front());
        container.pop();
    }
    return out << elements;
}

// Helper function to print std::priority_queue
template<typename T, typename Container, typename Compare>
ostream& operator<<(ostream& out, std::priority_queue<T, Container, Compare> pq) {
    out << "{";
    while (!pq.empty()) {
        out << " " << pq.top();
        pq.pop();
    }
    out << " }";
    return out;
}

#ifdef DBG
void dbg_out() { cerr << endl; }

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}

#define dbg(...) cerr << #__VA_ARGS__ << ":", dbg_out(__VA_ARGS__);
#define dbg_array(a, n) cerr << #a << ": { "; for(int i = 0; i < n; i++) cerr << a[i] << " "; cerr << "}\n";
#else
#define dbg(...)
#define dbg_array(a, n)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

bool check_sq(int x) {
    int sq = sqrt(x);
    while (sq*sq < x) sq++;
    while (sq*sq > x) sq--;
    return sq*sq == x;
}
const int inf = 1e9;

struct Node { // sum seg tree
	Node *l = 0, *r = 0;
	int lo, hi, mset = inf, madd = 0, val = 0;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of 0
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = l->val+r->val;
		}
		else val = v[lo];
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return val;
		push();
		return (l->query(L, R)+r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = l->val+r->val;
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x*(hi-lo);
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = l->val+r->val;
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

int calc_sqrt(int x) {
    assert(x >= 0);
    if (x == 0) return 0;
    int ret = sqrt(x);
    assert(ret >= 0);
    while (ret*ret > x) ret--;
    while (ret*ret <= x) ret++;
    return ret-1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    int a[n+1]; F0R(i, n) cin >> a[i+1];
    // keep track of the ones that are equal to square or 1 below it
    Node sqr(1, n+1); // 0 is not a square
    Node below_sqr(1, n+1);
    int f_arr[n+1]; f_arr[0] = 0;
    Node f(1, n+1);
    FOR(i, 1, n) {
        int val = f_arr[i-1]+a[i];
        f_arr[i] = calc_sqrt(val);
        f.add(i, i+1, f_arr[i]); // set it to f_arr[i]
        if (val && check_sq(val)) sqr.add(i, i+1, 0);
        else sqr.add(i, i+1, 1);
        if (check_sq(val+1)) below_sqr.add(i, i+1, 0);
        else below_sqr.add(i, i+1, 1);
    }
    dbg(f.query(n, n+1));
    while (q--) {
        int k, x; cin >> k >> x;
        dbg(k, x);
        // FOR(i, 1, n) cerr << f.query(i, i+1) << " "; cerr << nl;
        // int y = 0; FOR(i, 1, n) { cerr << y+a[i] << " "; y = calc_sqrt(y+a[i]); } cerr << nl;
        // FOR(i, 1, n) cerr << sqr.query(i, i+1) << " "; cerr << nl;
        // FOR(i, 1, n) cerr << below_sqr.query(i, i+1) << " "; cerr << nl;
        a[k] = x;
        // calc the next 8 or something manually
        rep(j, 0, 8) {
            if (k+j>n) break;
            int i = j+k;
            int oldf = f.query(i, i+1);
            // reset them
            if (!sqr.query(i, i+1)) sqr.add(i, i+1, 1);
            if (!below_sqr.query(i, i+1)) below_sqr.add(i, i+1, 1);

            int newval = f.query(i-1, i)+a[i];
            int newf = calc_sqrt(newval);
            f.add(i, i+1, newf-oldf);

            if (newval && check_sq(newval)) sqr.add(i, i+1, -1);
            if (check_sq(newval+1)) below_sqr.add(i, i+1, -1);
        }
        if (k+8>n) {
            dbg("more than k+8");
            cout << f.query(n, n+1) << nl;
            continue;
        }
        // now its been updated up to k+7
        // see if it bumps up k+8
        int prev = f.query(k+8, k+9);
        int nxt = calc_sqrt(f.query(k+7, k+8)+a[k+8]);
        if (nxt == prev) {
            dbg("no change in k+8");
            cout << f.query(n, n+1) << nl;
            continue;
        }
        dbg("change is", nxt-prev);
        assert(abs(nxt-prev) == 1);
        if (nxt > prev) { // check for bumping up
            // find the first 1 k+8 and after
            int lo = k+8, hi = n;
            while (lo < hi) {
                int mid = (lo+hi)/2;
                int sum = below_sqr.query(k+8, mid+1);
                if (sum==0) lo = mid+1;
                else hi = mid;
            }
            dbg(lo);
            // lo is the first 1 to show up, which means its not a sqr-1
            // update all the below_sqr to be 1
            assert(below_sqr.query(k+8, lo) == 0);
            below_sqr.add(k+8, lo, 1);
            assert(sqr.query(k+8, lo) == lo-(k+8));
            sqr.add(k+8, lo, -1); // update to 0s
            // add 1 to lo
            // reset it to 1
            if (!sqr.query(lo, lo+1)) sqr.add(lo, lo+1, 1);
            if (!below_sqr.query(lo, lo+1)) below_sqr.add(lo, lo+1, 1);

            int oldf = f.query(lo, lo+1);
            f.add(k+8, lo+1, 1);
            int newval = f.query(lo-1, lo)+a[lo];
            int newf = f.query(lo, lo+1);
            assert(newf == oldf+1);
            // assert(calc_sqrt(newval) == newf);
            if (newval && check_sq(newval)) sqr.add(lo, lo+1, -1);
            if (check_sq(newval+1)) below_sqr.add(lo, lo+1, -1);
        } else { // check for bumping down
            int lo = k+8, hi = n;
            while (lo < hi) {
                int mid = (lo+hi)/2;
                int sum = sqr.query(k+8, mid+1);
                if (sum==0) lo=mid+1;
                else hi = mid;
            }
            dbg(lo);
            // lo is the first 1 to show up, which means its not a sqr
            assert(sqr.query(k+8, lo) == 0);
            sqr.add(k+8, lo, 1);
            assert(below_sqr.query(k+8, lo) == lo-(k+8));
            below_sqr.add(k+8, lo, -1); // update to 0s
            // add 1 to lo
            // reset it to 1
            if (!sqr.query(lo, lo+1)) sqr.add(lo, lo+1, 1);
            if (!below_sqr.query(lo, lo+1)) below_sqr.add(lo, lo+1, 1);

            int oldf = f.query(lo, lo+1);
            f.add(k+8, lo+1, -1);
            int newval = f.query(lo-1, lo)+a[lo];
            int newf = f.query(lo, lo+1);
            assert(newf == oldf-1);
            // assert(calc_sqrt(newval) == newf);
            if (newval && check_sq(newval)) sqr.add(lo, lo+1, -1);
            if (check_sq(newval+1)) below_sqr.add(lo, lo+1, -1);
        }
        cout << f.query(n, n+1) << nl;
        
    }
    return 0;
}
