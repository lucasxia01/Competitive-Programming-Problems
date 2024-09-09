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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int a[n]; F0R(i, n-1) cin >> a[i+1];
    // assume the missing person is at the beginning to start
    bool seen[n+1]; memset(seen, 0, sizeof seen);
    F0R(i, n-1) seen[a[i+1]] = 1;
    FOR(i, 1, n) if (!seen[i]) a[0] = i;
    dbg_array(a, n);
    // now compute the answer for i
    ll cur = 0;
    // get the log_2 of n
    int m = 63 - __builtin_clzll(n);
    int tree[2*n]; F0R(i, n) tree[i+n] = a[i];
    FORd(i, 1, n-1) {
        cur += (tree[2*i]-tree[2*i+1])*(tree[2*i]-tree[2*i+1]);
        tree[i] = max(tree[2*i], tree[2*i+1]);
    }
    cout << cur << ' ';
    F0R(i, n-1) {
        // swap i with i+1
        // subtract all values on the paths of i and i+1
        int j = n+i, jj = n+i+1;
        while (j > 1) {
            cur -= (tree[j]-tree[j^1])*(tree[j]-tree[j^1]);
            if (j/2 != jj/2) cur -= (tree[jj]-tree[jj^1])*(tree[jj]-tree[jj^1]);
            j /= 2;
            jj /= 2;
        }
        dbg("intermediate: ", cur);
        // now swap the two
        swap(tree[n+i], tree[n+i+1]);
        // recalculate the winners
        
        // add all values on the paths of i and i+1
        j = n+i, jj = n+i+1;
        while (j > 1) {
            cur += (tree[j]-tree[j^1])*(tree[j]-tree[j^1]);
            if (j/2 != jj/2) cur += (tree[jj]-tree[jj^1])*(tree[jj]-tree[jj^1]);
            j /= 2;
            jj /= 2;
            tree[j] = max(tree[2*j], tree[2*j+1]);
            tree[jj] = max(tree[2*jj], tree[2*jj+1]);
        }
        // F0R(j, 2*n-1) {
        //     cout << tree[j+1] << ' ';
        // } cout << nl;
        cout << cur << ' ';
    }
    cout << nl;
    return 0;
}
