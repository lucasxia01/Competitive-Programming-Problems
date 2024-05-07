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
    int n, m; cin >> n >> m;
    // be greedy and don't form self loops
    int w[n]; F0R(i, n) cin >> w[i];
    bool in[n], out[n]; F0R(i, n) in[i] = out[i] = 1;
    // everything alive so far
    F0R(i, m)  {
        int a, b; cin >> a >> b;
        a--; b--;
        // a to b edge
        out[a] = 0;
        in[b] = 0;
    }
    set<pi> outs, ins;
    F0R(i, n) {
        if (out[i]) outs.insert({-w[i], i});
        if (in[i]) ins.insert({-w[i], i});
    }
    // ordered from least to greatest
    bool edge = 0;
    if (outs.rbegin()->s == ins.rbegin()->s) edge = 1;
    ll ans = 0;
    while (sz(outs)) {
        auto [x, y] = *outs.begin();
        x = -x;
        // make sure the last one isn't a self loop though!
        auto it = ins.begin();
        if (sz(outs) == 3) {
            // just try all 6 permutations
            vpi v1; trav(o, outs) v1.pb({-o.f, o.s});
            vpi v2; trav(i, ins) v2.pb({-i.f, i.s});
            vi v = {0, 1, 2};
            ll tmp = 0;
            do {
                bool ok = 1;
                ll sum = 0;
                F0R(i, 3) {
                    if (v1[i].s == v2[v[i]].s) ok = 0;
                    sum += 1LL*(v1[i].f+v2[v[i]].f)*(v1[i].f+v2[v[i]].f);
                }
                if (ok) ckmax(tmp, sum);
            } while (next_permutation(all(v)));
            ans += tmp;
            break;
        }
        if (sz(outs) == 2) {
            // we must choose the better one between the two cases
            ll v1 = 0;
            auto [x2, y2] = *ins.begin(); x2 = -x2;
            auto [a, b] = *outs.rbegin(); a = -a;
            auto [a2, b2] = *ins.rbegin(); a2 = -a2;
            if (y2 != y) v1 += 1LL*(x + x2) * (x + x2);
            if (b2 != b) v1 += 1LL*(a + a2) * (a + a2);
            ll v2 = 0; // cross
            if (y != b2) v2 += 1LL*(x+a2)*(x+a2);
            if (b != y2) v2 += 1LL*(a+x2)*(a+x2);
            dbg(v1, v2);
            ans += max(v1, v2);
            break;
        }
        if (it->s == y) it++;
        auto [x2, y2] = *it;
        x2 = -x2;
        outs.erase(outs.begin());
        ins.erase(it);
        ans += 1LL*(x + x2) * (x + x2);
    }
    cout << ans << nl;
    return 0;
}
