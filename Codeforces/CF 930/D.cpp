#include <bits/stdc++.h>

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
const int SQRTN = 440;

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

struct Tree {
	typedef int T;
	static constexpr T unit = 0;
	T f(T a, T b) { return (a|b); } // (any associative fn)
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, v; cin >> n >> v;
        int a[n]; F0R(i, n) cin >> a[i];
        int b[n]; F0R(i, n) cin >> b[i];
        // compress a[i]
        vpi u; F0R(i, n) u.pb({a[i], i});
        sort(all(u));
        int ansMap[n], loc[n];
        F0R(i, n) {
            ansMap[i] = u[i].f;
            a[u[i].s] = i;
            loc[i] = u[i].s;
        }

        // now divide them into sqrtn chunks
        int NCHUNKS = ((n+SQRTN-1)/SQRTN);
        vpi segs[NCHUNKS];
        F0R(i, NCHUNKS) {
            int val = i*SQRTN;
            int cur = 0;
            F0R(j, n+1) {
                if (j == n || a[j] >= val) {
                    // end of a section
                    segs[i].pb({j, (cur>=v)});
                    cur = 0;
                } else cur |= b[j];
            }
        }
        // we need fenwick trees for these
        vector<FT> f;
        F0R(i, NCHUNKS) {
            FT cur(sz(segs[i]));
            int j = 0;
            trav(p, segs[i]) {
                cur.update(j, p.s);
                j++;
            }
        }

        // we need a segtree for keeping track of ORs
        Tree segTree(n);
        F0R(i, n) segTree.update(i, b[i]);

        int q; cin >> q;
        while (q--) {
            int type; cin >> type;
            if (type == 1) {
                int idx, x; cin >> idx >> x; idx--;
                // need to make SQRTN updates
                F0R(i, NCHUNKS) {
                    // lower_bound for which segment its in
                    auto it = lower_bound(all(segs[i]), mp(idx, -1));
                    assert(it != segs[i].end());
                    int j = it - segs[i].begin();
                    int R = it->f;
                    int L = -1;
                    if (it != segs[i].begin()) {
                        it--;
                        L = it->f;
                    }
                    // update this range's answer to [L+1, idx-1] | x | [idx+1, R-1]
                    segTree.update(idx, x);
                    int val = segTree.query(L+1, R);
                    f[i].update(j, (val >= v));
                }
            } else {
                // check for which chunk stops working
                int l, r; cin >> l >> r; l--; r--;
                int chunk = -1;
                F0Rd(i, NCHUNKS) {
                    auto itL = lower_bound(all(segs[i]), mp(l-1, -1));
                    int l_idx = itL - segs[i].begin();
                    auto itR = lower_bound(all(segs[i]), mp(r, -1));
                    int r_idx = itR - segs[i].begin();
                    // check if they're in the same segment
                    if (itL == itR) {
                        // then just query segtree here
                        int val = segTree.query(l, r+1);
                        if (val < v) {
                            chunk = i;
                            break;
                        }
                    } else {
                        // different chunks
                        bool val = (segTree.query(l, itL->f) >= v);
                        val |= (segTree.query(itR->f+1, r+1) >= v);
                        if (f[i].query(r_idx+1)-f[i].query(l_idx+1)) val = 1;
                        if (!val) {
                            chunk = i;
                            break;
                        }
                        
                    }
                }
                assert(chunk != -1);
                // now we know it fails at chunk*SQRTN and succeeds at (chunk+1)*SQRTN
                set<pi> curSegs;
                FOR(i, chunk*SQRTN, (chunk+1)*SQRTN-1) {
                    int idx = loc[i];
                    auto it = lower_bound(all(segs[chunk]), mp(idx, -1));
                    assert(it->f == idx);
                    curSegs.lower_bound(mp(it->f, ))
                }
            }
        }

    }
    return 0;
}
