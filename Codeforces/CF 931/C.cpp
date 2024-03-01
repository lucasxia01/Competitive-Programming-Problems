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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        cout << "? 1 1" << endl;
        cout.flush();
        int d1; cin >> d1;
        // we know its on diagonal d
        cout << "? " << n << " " << m << endl;
        cout.flush();
        int d2; cin >> d2;
        d2 = n+m-2-d2;
        // now try a third corner
        cout << "? " << n << " " << 1 << endl;
        cout.flush();
        int d3; cin >> d3;
        // its on d1 diag or d2 diag
        // x+y = d1 or x+y = n+m-2-d2
        // dist from n-1, 0 is d3
        int a = abs(n-1-d1);
        int b = abs(n-1-d2);
        // then its in increments of 2
        vpi p;
        if (d3>=a && (d3-a)%2==0) {
            int rem = (d3-a)/2;
            if (d1 < n-1) {
                int x = n-1-a, y = 0;
                x -= rem; y += rem;
                if (x >= 0 && y < m)
                    p.pb({x, y});
            } else {
                int x = n-1, y = a;
                x -= rem; y += rem;
                if (x >= 0 && y < m)
                    p.pb({x, y});
            }
        }

        if (d3 >= b && (d3-b)%2==0) {
            int rem = (d3-b)/2;
            if (d2 < n-1) {
                int x = n-1-b, y = 0;
                x -= rem; y += rem;
                if (x >= 0 && y < m)
                    p.pb({x, y});
            } else {
                int x = n-1, y = b;
                x -= rem; y += rem;
                if (x >= 0 && y < m)
                    p.pb({x, y});
            }
        }
        assert(sz(p) >= 1);
        if (sz(p) == 1) {
            cout << "! " << p[0].f+1 << " " << p[0].s+1 << endl;
            cout.flush();
        } else {
            cout << "? " << p[0].f+1 << " " << p[0].s+1 << endl;
            cout.flush();
            int ans; cin >> ans;
            if (ans != 0) {
                // assert(ans == abs(p[0].f-p[1].f) + abs(p[0].s-p[1].s));
                cout << "! " << p[1].f+1 << " " << p[1].s+1 << endl;
            } else {
                cout << "! " << p[0].f+1 << " " << p[0].s+1 << endl;
            }
        }
    }
    return 0;
}
