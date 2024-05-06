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

const int MX = 2e5+5;

int n, k;
vi gr[MX];
int ans[MX], sum[MX], cnt[MX];
void go(int v, int p, int d) {
    int ret = d;
    int c = 1;
    trav(u, gr[v]) {
        if (u == p) continue;
        go(u, v, d+1);
        ret += sum[u];
        c += cnt[u];
    }
    sum[v] = ret;
    cnt[v] = c;
    dbg(v, ret, c);
}


void solve(int v, int p, int d, int L, int R, int state, int target) {
    dbg(v, L, R, state, target);
    assert(cnt[v] == R-L+1);
    assert(L <= R);
    if (state == 0) { // increasing subtree
        dbg("assigning", v, L);
        int newL = L;
        ans[v] = L;
        newL++;
        trav(u, gr[v]) {
            if (u == p) continue;
            solve(u, v, d+1, newL, newL+cnt[u]-1, 0, -1);
            newL += cnt[u];
        }
        assert(newL == R+1);
    } else if (state == 1) { // decreasing subtree
        dbg("assigning", v, R);
        ans[v] = R;
        int newR = R;
        newR--;
        trav(u, gr[v]) {
            if (u == p) continue;
            solve(u, v, d+1, newR-cnt[u]+1, newR, 1, -1);
            newR -= cnt[u];
        }
        assert(newR == L-1);
    } else { // we are still finding where to recurse
        int total = 0; 
        int newR = R;
        bool done = 0;
        trav(u, gr[v]) {
            if (u == p) continue;
            // max answer in this subtree is
            int cur = sum[u] - cnt[u]*d;
            dbg(u, total, cur, cnt[u], sum[u], cnt[u], d);
            if (done) {
                solve(u, v, d+1, newR-cnt[u]+1, newR, 1, -1); // we want 0 from this subtree
                newR -= cnt[u];
            } else if (cur+total <= target) {
                solve(u, v, d+1, newR-cnt[u]+1, newR, 0, -1);
                total += cur;
                newR -= cnt[u]; // all of these are sent to inc
            } else { // adding this would exceed target
                dbg("exceeding");
                int rem = target-total;
                if (rem >= cnt[u]) {
                    rem -= cnt[u];
                    ans[v] = newR-cnt[u];
                    dbg("assigning", v, newR-cnt[u]);
                    solve(u, v, d+1, newR-cnt[u]+1, newR, 2, rem);
                } else {
                    ans[v] = newR;
                    dbg("assigning", v, newR);
                    solve(u, v, d+1, newR-cnt[u], newR-1, 2, rem);
                }
                newR -= cnt[u]+1;
                done = 1;
            }
        }
        if (!done) {
            dbg("assigning", v, newR);
            ans[v] = newR;
            newR--;
        }
        dbg(v, d, cnt[v], L, R, newR);
        assert(newR == L-1);
    }
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v;
        gr[u].pb(v);
        gr[v].pb(u);
    }
    go(1, 0, 0);
    k -= n;
    if (k < 0 || sum[1] < k) {
        cout << "No" << nl;
        return 0;
    }
    solve(1, 0, 0, 1, n, 2, k);
    cout << "Yes" << nl;
    rep(i, 1, n+1) cout << ans[i] << " ";
    cout << nl;
    return 0;
}
