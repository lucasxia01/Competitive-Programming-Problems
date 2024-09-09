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
const int SQRTN = 100;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    int a[n]; F0R(i, n) cin >> a[i];
    vector<array<int, 4>> smallqs;
    vector<array<int, 4>> largeqs;
    F0R(i, q) {
        // read in l, r, k
        array<int, 4> cur;
        F0R(j, 3) cin >> cur[j];
        cur[0]--; cur[1]--;
        cur[3] = i;
        if (cur[2] < SQRTN) smallqs.pb(cur);
        else largeqs.pb(cur);
    }
    // for things with k < SQRTN, we will just store the next k things of every value A[i]
    set<pi> vals[SQRTN];
    vi pos[n+1];
    F0R(i, n) pos[a[i]].pb(i);
    int ptr[n+1]; FOR(i, 1, n) ptr[i] = 0;
    FOR(i, 1, n) {
        // up to SQRTN
        F0R(j, min(SQRTN, sz(pos[i]))) {
            dbg("inserting", j, pos[i][j], i);
            vals[j].insert({pos[i][j], i});
        }
    }
    sort(all(smallqs));
    int ans[q]; F0R(i, q) ans[i] = -2;
    // now go through them
    int p = 0;
    F0R(i, n) {
        while (p < sz(smallqs) && smallqs[p][0] == i) {
            dbg(smallqs[p][0], smallqs[p][1], smallqs[p][2], smallqs[p][3]);
            int k = smallqs[p][2]-1;
            assert(k < SQRTN);
            // check the min of this set and compare it to r
            auto it = vals[k].begin();
            if (it == vals[k].end() || it->f > smallqs[p][1]) {
                dbg("setting ans", smallqs[p][3], -1);
                ans[smallqs[p][3]] = -1;
            } else {
                dbg("setting ans", smallqs[p][3], it->s);
                ans[smallqs[p][3]] = it->s;
            }
            p++;
        }
        // now we must transition to i+1, so we lose a[i]
        int val = a[i];
        int pt = ptr[a[i]];
        auto& v = pos[val];
        FOR(j, pt, min(pt+SQRTN, sz(v))-1) {
            auto& s = vals[j-pt];
            dbg(i, j, val, pt);
            auto it = s.find({v[j], val});
            s.erase(it);
            if (j+1 < sz(v)) s.insert({v[j+1], val});
        }
        ptr[a[i]]++;
    }

    F0R(i, q) cout << ans[i] << nl;
    
    return 0;
}
