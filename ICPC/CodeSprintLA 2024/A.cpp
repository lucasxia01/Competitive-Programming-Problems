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

int n, k, d, q;
vpi breads[MX]; // for each bread type, a list of positions and the index of the person in sorted order
int find_next(int pos, int type) { // return index of person it jumped to
    // we are at pos and we want next position of type bread
    pi key = mp(pos, -1);
    int idx = lower_bound(all(breads[type]), key) - breads[type].begin();
    if (idx == breads[type].size()) idx = 0;
    return breads[type][idx].s;
}
// indexed by the person
vpi jmp[MX]; // jumps of powers of 2 from each position, index of person it jumped to and distance

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> k >> d >> q;
    int pos[n], type[n];
    F0R(i, n) cin >> pos[i];
    F0R(i, n) cin >> type[i];
    F0R(i, n) breads[type[i]].pb({pos[i], i});
    F0R(i, k) sort(all(breads[i]));
    F0R(i, n) {
        // compute the jumps
        vpi tmp(30); // compute jumps up to 2^29
        jmp[i] = tmp;
        int nxtIdx = find_next(pos[i], (type[i]+1)%k);
        jmp[i][0] = {nxtIdx, (pos[nxtIdx]-pos[i]+d)%d};
    }
    FOR(j, 1, 29) {
        F0R(i, n) {
            auto [nxtIdx, dist] = jmp[i][j-1];
            int nxtPos = (pos[i]+dist)%d;
            int nxtType = (type[i]+(1LL<<(j-1)))%k;
            auto [nxtnxtIdx, dist2] = jmp[nxtIdx][j-1];
            jmp[i][j] = {nxtnxtIdx, dist+dist2};
        }
    }
    while (q--) {
        int startPos, startType, jmps; cin >> startPos >> startType >> jmps;
        if (jmps == 0) {
            cout << 0 << nl;
            continue;
        }
        dbg(startPos, startType, jmps);
        ll ans = 0;
        auto idx = find_next(startPos, startType);
        int dist = (pos[idx]-startPos+d)%d;
        int curPos = (startPos+dist)%d;
        int curType = startType;
        ans += dist;
        // we want to deliver jmps-1 more breads
        int curJmps = 1;
        dbg(curPos, curType, dist, ans, curJmps);
        F0Rd(j, 30) {
            if (curJmps+(1LL<<j) > jmps) continue;
            auto [nxtIdx, dist] = jmp[idx][j];
            idx = nxtIdx;
            curPos = (curPos+dist)%d;
            int curType = (curType+(1LL<<j))%k;
            ans += dist;
            curJmps += (1LL<<j);
        }
        cout << ans << nl;
    }
    return 0;
}
