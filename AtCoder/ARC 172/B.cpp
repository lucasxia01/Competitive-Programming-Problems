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
const ll MOD = 998244353;
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

const int MX = 5e5+5;


template<int sz> struct Combo {
    ll fac[sz+1], ifac[sz+1];
    Combo() {
        fac[0] = 1LL;
        for (int i = 1; i <= sz; i++) {
            fac[i] = fac[i - 1] * i % MOD;
        }
        ifac[sz] = mod_inv(fac[sz]);
        for (int i = sz; i > 0; i--) {
            ifac[i-1] = ifac[i] * i % MOD;
        }
    }
 
    ll mod_pow(ll a, ll b) {
        if (b == 0) return 1LL;
        ll p = mod_pow(a, b >> 1);
        p = p * p % MOD;
        if (b & 1)
            p = p * a % MOD;
        return p;
    }
 
    ll mod_inv(ll n) {
        return mod_pow(n, MOD - 2);
    }
 
    ll comb(ll n, ll r) {
        if (n < r || n < 0 || r < 0) return 0LL;
        ll res = (fac[n] * ifac[r] % MOD) * ifac[n - r] % MOD;
        return res;
    }
};
 
ll mod(ll x) {
    return (x % MOD + MOD) % MOD;
}
 
ll modAdd(ll x, ll y) {
    return ( (x % MOD + y % MOD) % MOD + MOD ) % MOD;
}
 
 
ll gcd(ll a, ll b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a%b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin.tie(0); cout.tie(0);
    Combo<MX> cm;
    ll n, k, l; cin >> n >> k >> l;
    // for first k, pick anything except last two different
    ll ans = 1;
    F0R(i, n-k) {
        ans = mod(1LL*ans*(l-i));
    }
    F0R(i, k) {
        ans = mod(1LL*ans*(l-(n-k)));
    }
    cout << ans << nl;
    return 0;
}
