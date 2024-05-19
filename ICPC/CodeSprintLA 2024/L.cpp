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

const int MX = 1e5+5;
const int MAXT = 1e9+5;

int n, T;
vi gr[MX];
int h[MX];
int t[MX];
int ans[MX];

using Type = int;
Type extended_euclid(Type a, Type b, Type &x, Type &y) {
  Type xx = y = 0;
  Type yy = x = 1;
  while (b) {
    Type q = a / b;
    Type t = b; b = a % b; a = t;
    t = xx; xx = x - q * xx; x = t;
    t = yy; yy = y - q * yy; y = t;
  }
  return a;
}
// finds x such that x % m1 = a1, x % m2 = a2. m1 and m2 may not be coprime
// here, x is unique modulo m = lcm(m1, m2). returns (x, m). on failure, m = -1.
pair<Type, Type> CRT(Type a1, Type m1, Type a2, Type m2) {
  Type p, q;
  Type g = extended_euclid(m1, m2, p, q);
  if (a1 % g != a2 % g) return make_pair(0, -1);
  Type m = m1 / g * m2;
  p = (p % m + m) % m;
  q = (q % m + m) % m;
  return make_pair((p * a2 % m * (m1 / g) % m + q * a1 % m * (m2 / g) % m) %  m, m);
}

void dfs(int v, int d) {
    h[v] = d;
    for (int u : gr[v]) {
        dfs(u, d+1);
    }
}
int solve(int v, int offset, int period, int prevT) {
    if (offset > MAXT) return 0;
    if (period > MAXT) period = -1;
    int realT = min(prevT, t[v]); // this is when this node can be reached
    dbg(v, offset, period, prevT, realT, t[v]);
    // find how often this thing is reached
    int cnt = 0;
    if (period == -1) { // period is infinity
        if (offset != -1 && offset < realT) cnt++;
    } else {
        cnt = realT/period;
        assert(offset != -1);
        if (offset < realT%period) cnt++;
    }
    // we come to this one cnt times in the time period realT
    int idx = 0;
    int sum = 0;
    trav(u, gr[v]) {
        int newOffset, newPeriod;
        if (period != -1) {
            pl res = CRT(offset, period, idx, sz(gr[v]));
            if (res.s == -1) {
                idx++;
                continue;
            } else {
                newOffset = res.f;
                newPeriod = res.s;
            }
        } else {
            if (offset%sz(gr[v]) == idx) {
                newOffset = offset;
                newPeriod = -1;
            } else {
                idx++;
                continue;
            }
        }
        sum += solve(u, newOffset, newPeriod, realT);
        idx++;
    }
    ans[v] = cnt-sum;
    return cnt;
}

int ans2[MX];
int idx[MX];

void slowsolve(int curT, int v) {
    if (sz(gr[v]) == 0 || curT >= t[gr[v][idx[v]]]) {
        ans2[v]++;
        dbg(curT, v);
        return;
    }
    slowsolve(curT, gr[v][idx[v]]);
    idx[v] = (idx[v]+1)%sz(gr[v]);
}
// OVERFLOW WATCH
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> T;
    F0R(i, n) {
        int x; cin >> x;
        F0R(j, x) {
            int y; cin >> y; y--;
            gr[i].pb(y);
        }
    }
    dfs(0, 0);
    
    F0R(i, n-1) {
        int a, b, x; cin >> a >> b >> x; a--; b--; x--;
        if (h[a] > h[b]) swap(a, b);
        t[b] = x;
    }
    t[0] = T;
    solve(0, 0, 1, T);
    // F0R(i, T) slowsolve(i, 0);
    F0R(i, n) cout << ans[i] << " "; cout << nl;
    // F0R(i, n) cout << ans2[i] << " "; cout << nl;
    // F0R(i, n) assert(ans[i] == ans2[i]);
    return 0;
}
