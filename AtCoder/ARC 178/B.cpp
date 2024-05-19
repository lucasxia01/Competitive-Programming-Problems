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

const int MX = 3e5+5;

// binary exp
long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a)%MOD;
        a = (a * a)%MOD;
        b >>= 1;
    }
    return res;
}

ll mod(ll x) {
    return (x%MOD+MOD)%MOD;
}

// MAKE SURE TO TEST EACH CASE
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int INV2 = binpow(2, MOD-2);
    int t; cin >> t;
    while (t--) {
        int a1, a2, a3; cin >> a1 >> a2 >> a3;
        if (a1 < a2) swap(a1, a2);
        if (a1 != a3 && a1 != a3-1) {
            cout << 0 << nl;
            continue;
        }
        ll ans = 0;
        if (a1 == a3) { // we don't want to carry
            // first case is we don't put all 9s in the a1-a2
            if (a1 != a2) {
                int num_ones = mod(binpow(10, a1)-binpow(10, a1-1)-binpow(10, a2));
                int num_twos = mod(binpow(10, a2)-binpow(10, a2-1));
                ans += mod(num_ones*num_twos);
                ans = mod(ans);
            }
            // second is we put all 9s in the a1-a2, but we don't carry in bottom a2
            ll hi = mod(binpow(10, a2)-mod(2*binpow(10, a2-1)));
            ll total = mod(mod(hi*(hi+1))*INV2);
            if (a1 != a2) {
                // we can put things below 10**(a2-1) for a1
                hi = mod(binpow(10, a2)-mod(binpow(10, a2-1)));
                total = mod(mod(hi*(hi+1))*INV2);
            }
            ans += total;
            ans = mod(ans);
        } else { //  we want to carry
            // we must put all 9s in the diff
            // see how many things sum to at least 10**a2
            if (a1 != a2) {
                ll lo = binpow(10, a2-1);
                ll hi = mod(binpow(10, a2)-1);
                ll cnt = mod(binpow(10, a2)-binpow(10, a2-1));
                ll total = mod(mod(cnt*(lo+hi))*INV2);
                ans += total;
                ans = mod(ans);
            } else { // we can't use the bottom part for 1
                ll lo = binpow(10, a2-1);
                ll hi = mod(binpow(10, a2)-binpow(10, a2-1)-1);
                ll cnt = mod(hi-lo+1);
                ll total = mod(mod(cnt*(lo+hi))*INV2);
                // the remaining part above hi
                ll cnt2 = lo;
                total = mod(total+mod(cnt2*(hi+1)));
                ans += total;
                ans = mod(ans);

            }
        }
        cout << ans << nl;
    }
    return 0;
}
