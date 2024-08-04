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
    int n; cin >> n;
    int p[n]; F0R(i, n) cin >> p[i];
    int q[n]; F0R(i, n) cin >> q[i];
    F0R(i, n) {
        p[i]--;
        q[i]--;
    }
    // write down n things that partition the columns
    int posp[n]; F0R(i, n) posp[p[i]] = i;

    int pos[n]; F0R(i, n) pos[q[i]] = i;
    string s = ""; F0R(i, n) s += '0';
    vector<string> v;
    F0R(i, n) {
        v.pb(s);
        s[q[n-1-i]] = '1';
    }
    sort(all(v));
    F0R(i, n) cout << v[posp[i]] << nl;
    // char m[n][n]; 
    // F0R(i, n) F0R(j, n) m[i][j] = v[p[i]][j];
    // F0R(k, n-1) {
    //     bool ok = 1;
    //     F0R(j, n) {
    //         if (m[posp[k]][j] < m[posp[k+1]][j]) {
    //             break;
    //         } else if (m[posp[k]][j] > m[posp[k+1]][j]) {
    //             dbg("break", k, j, m[posp[k]][j], m[posp[k+1]][j]);
    //             ok = 0;
    //             break;
    //         }
    //     }
    //     if (!ok) {
    //         dbg("row", k);
    //     }
    //     assert(ok);
    // }

    // F0R(k, n-1) {
    //     bool ok = 1;
    //     F0R(i, n) {
    //         if (m[i][pos[k]] < m[i][pos[k+1]]) {
    //             break;
    //         } else if (m[i][pos[k]] > m[i][pos[k+1]]) {
    //             ok = 0;
    //             break;
    //         }
    //     }
    //     if (!ok) {
    //         dbg("col", k);
    //     }
    //     assert(ok);
    // }
    
    return 0;
}
