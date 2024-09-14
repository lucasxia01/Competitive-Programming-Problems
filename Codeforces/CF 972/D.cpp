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

ll my_gcd(ll a, ll b) {
    if (a < b) return my_gcd(b, a);
    if (b == 0) return a;
    return my_gcd(b, a%b);
}
// sparse table to calculate gcd on range of elements
template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = my_gcd(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
        if (a == b) return 0;
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return my_gcd(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vi a(n); F0R(i, n) cin >> a[i];
        vi b(n); F0R(i, n) cin >> b[i];
        RMQ<int> ra(a);
        RMQ<int> rb(b);
        // for each find all the drops in gcd (only log n) of them
        vi pt; pt.pb(n);
        int gcda = 0, gcdb = 0;
        F0Rd(i, n) {
            int preva = gcda;
            gcda = my_gcd(gcda, a[i]);
            int prevb = gcdb;
            gcdb = my_gcd(gcdb, b[i]);
            if (preva != gcda || prevb != gcdb) {
                pt.pb(i);
                pt.pb(i-1);
                pt.pb(i+1);
            }
        }
        pt.pb(0);
        reverse(all(pt));
        sort(all(pt));
        dbg(pt);
        int ans = 0;
        ll cnt = 0;
        F0R(i, n) {
            // we're considering swapping the range from i to some j
            // first, we need to find all the places where gcd of the range [i, j) drops, with logn binary searches I guess
            vi drops;
            int cur = i;
            int curgcd = 0;
            while (cur < n) {
                int l = cur, r = n;
                while (l < r) {
                    int mid = (l+r)/2;
                    if (ra.query(i, mid) != curgcd) {
                        r = mid;
                    } else l = mid+1;
                }
                drops.pb(l);
                drops.pb(l-1);
                drops.pb(l+1);
                cur = l;
                curgcd = ra.query(i, cur);
                dbg(cur, curgcd);
            }
            cur = i;
            curgcd = 0;
            while (cur < n) {
                int l = cur, r = n;
                while (l < r) {
                    int mid = (l+r)/2;
                    if (rb.query(i, mid) != curgcd) {
                        r = mid;
                    } else l = mid+1;
                }
                drops.pb(l);
                drops.pb(l-1);
                drops.pb(l+1);
                cur = l;
                curgcd = rb.query(i, cur);
                dbg(cur, curgcd);
            }
            sort(all(drops));
            drops.pb(INF);
            dbg(i, drops);
            pt.pb(INF);
            // so we change going from drop[i]-1 to drop[i]
            // we also change going from pt[i]-1 to pt[i]
            // now just go over all the places 
            int ptr = 0;
            int dropptr = 0;
            int prevpt = i;
            while (dropptr < sz(drops) && ptr < sz(pt)) {
                int j;
                if (drops[dropptr] < pt[ptr]) {
                    j = drops[dropptr];
                    dropptr++;
                } else {
                    j = pt[ptr];
                    ptr++;
                }
                if (j == INF) break;
                if (j == prevpt) continue;
                if (j <= i) continue;
                if (j > n) continue;
                // consider [i, j)
                dbg(i, j, n);
                int cura = my_gcd(my_gcd(ra.query(0, i), rb.query(i, j)), ra.query(j, n));
                int curb = my_gcd(my_gcd(rb.query(0, i), ra.query(i, j)), rb.query(j, n));
                int total = cura + curb;
                int amt = j-prevpt;
                if (ckmax(ans, total)) {
                    dbg(ans, i, j, cura, curb, amt);
                    cnt = amt;
                } else if (ans == total) {
                    dbg(ans, i ,j, cura, curb, amt);
                    cnt += amt;
                }
                prevpt = j;
            }      
        }
        cout << ans << " " << cnt << nl;
    }
    return 0;
}
