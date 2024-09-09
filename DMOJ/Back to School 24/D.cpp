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
    int n, k; cin >> n >> k;
    int a[n]; F0R(i, n) {
        cin >> a[i];
        a[i]--;
    }
    // for each k, count how many things are not freed
    int m[n][k];
    F0R(i, n) F0R(j, k) cin >> m[i][j];
    // reorder based on a
    int c[n][k];
    F0R(i, n) F0R(j, k) c[i][j] = m[a[i]][j];
    // F0R(i, n) {
    //     F0R(j, k) cout << c[i][j] << " ";
    //     cout << nl;
    // }
    // now find where things go right and wrong for each one
    bool saved[n-1]; F0R(i, n-1) saved[i] = 0;
    vi bad[n-1];
    int cnt[k]; F0R(i, k) cnt[i] = 0;
    vi saves[k];
    F0R(j, k) F0R(i, n-1) {
        if (c[i][j] > c[i+1][j]) saves[j].pb(i);
        else if (c[i][j] < c[i+1][j]) {
            bad[i].pb(j);
            cnt[j]++;
        }
    }
    // keep a min priorityqueue of the things with cnt = 0;
    priority_queue<int, vi, greater<int>> good;
    F0R(i, k) {
        dbg(i, cnt[i]);
        if (cnt[i] == 0) good.push(i);
    }
    vi ans;
    while (!good.empty()) {
        int col = good.top(); good.pop();
        dbg(col);
        ans.pb(col);
        // figure out what this saves
        trav(b, saves[col]) {
            if (!saved[b]) {
                dbg("saves", b);
                // clean it out!
                trav(j, bad[b]) {
                    cnt[j]--;
                    dbg(b, j);
                    if (cnt[j] == 0) good.push(j);
                }
                saved[b] = 1;
            }
        }
    }
    if (sz(ans) != k) {
        cout << -1 << nl;
        return 0;
    }
    trav(x, ans) cout << x+1 << " ";
    cout << nl;
    return 0;
}
