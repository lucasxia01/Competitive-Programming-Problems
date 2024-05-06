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
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define repd(i, a, b) for(int i = (b)-1; i >= (a); --i)

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int a = -1, b = -1;
    vi ans(n, -1);
    pi p[n];
    vector<array<int, 3> > v;
    int dir = -1;
    rep(i, 0, n) {
        int l, r; cin >> l >> r;
        p[i] = {l, r};
        if (a == -1) {
            a = l, b = r;
        } else {
            if (r < a) { // forced down
                if (v.empty()) {
                    v.pb({0, a, 1});
                } else if (v.back()[2] == 0) v.pop_back();
                v.pb({i, r, 0});
                // pull down the previous
                a = r, b = r;
                dir = 1;
            } else if (l > b) { // this is a forced UP
                if (v.empty()) {
                    v.pb({0, b, 0});
                } else if (v.back()[2] == 1) v.pop_back();
                v.pb({i, l, 1});
                a = l, b = l;
                dir = 0;
            } else {
                // we are overlapping
                a = max(a, l), b = min(b, r);
                assert(a <= b);
            }
        }
    }
    if (dir == -1) {
        v.pb({0, a, 0});
        v.pb({n-1, a, 1});
    } else if (dir == 0) v.pb({n-1, a, 0});
    else v.pb({n-1, b, 1});
    // now for every min (marked as 0), do stuff
    int m = v.size();
    rep(i, 0, m) {
        if (v[i][2] == 1) continue;
        dbg(v[i][0], v[i][1], v[i][2]);
        if (i != 0) {
            // go from v[i-1][0] to v[i][0] in reverse
            int cur = v[i][1];
            repd(j, v[i-1][0], v[i][0]+1) {
                cur = max(cur, p[j].f);
                ans[j] = cur;
            }
            assert(cur == v[i-1][1]);
        }
        if (i != m-1) {
            // go from v[i][0] to v[i+1][0]
            int cur = v[i][1];
            rep(j, v[i][0], v[i+1][0]+1) {
                cur = max(cur, p[j].f);
                ans[j] = cur;
            }
            assert(cur == v[i+1][1]);
        }
    }
    trav(u, ans) cout << u << ' ';
    cout << nl;
    return 0;
}
