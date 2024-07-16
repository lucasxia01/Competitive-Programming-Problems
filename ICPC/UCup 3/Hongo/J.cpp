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
    int n, l, r; cin >> n >> l >> r;
    vi a(n); F0R(i, n) cin >> a[i];
    reverse(all(a));
    // count the number of numbers between l and r such that we use an even amount of each coin
    int full = 0;
    int pref = -1;
    int suf = -1;
    // do the first number by itself
    pi lo = {l/a[0], l%a[0]};
    pi hi = {r/a[0], r%a[0]};
    if (lo.f%2 == 0) {
        suf = lo.s;
        lo.f += 2;
    } else {
        suf = -1;
        lo.f++;
    }
    if (hi.f%2 == 0) {
        pref = hi.s;
        hi.f -= 2;
    } else {
        pref = -1;
        hi.f--;
    }
    full = (hi.f-lo.f+2)/2;
    FOR(i, 1, n-1) {
        dbg(suf, pref, full);
        // suf goes from suf to a[i-1]-1
        int fullcnt = 0;
        if (suf != -1) {
            lo = {suf/a[i], suf%a[i]};
            hi = {(a[i-1]-1)/a[i], (a[i-1]-1)%a[i]};
            if (lo.f%2 == 0) {
                suf = lo.s;
                lo.f += 2;
            } else {
                suf = -1;
                lo.f++;
            }
            fullcnt += (hi.f-lo.f+2)/2;
        }
        // pref goes from 0 to pref
        if (pref != -1) {
            lo = {0, 0};
            hi = {pref/a[i], pref%a[i]};
            if (hi.f%2 == 0) {
                pref = hi.s;
                hi.f -= 2;
            } else {
                pref = -1;
                hi.f--;
            }
            fullcnt += (hi.f-lo.f+2)/2;
        }
        // lastly the fulls go from 0 to a[i-1]-1
        // we have full amount of fulls
        lo = {0, 0};
        hi = {(a[i-1]-1)/a[i], (a[i-1]-1)%a[i]};
        if (hi.f%2) hi.f--;
        fullcnt += full * ((hi.f-lo.f+2)/2);
        full = fullcnt;
    }
    // now after the 1, see how many fulls we have
    int total = r-l+1;
    dbg(suf, pref, full, total);
    full += (suf != -1) + (pref != -1);
    cout << total-full << nl;
    return 0;
}
