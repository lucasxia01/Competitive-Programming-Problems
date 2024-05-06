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

/*
 String Hashing class
 Finds prefix and rev hashes and uses this to compute a prefix/rev hash for any substring
 Tested on Codeforces Global Round 7 D1/D2 (3/19/2020)
 */
struct stringHash {
    int base;
    int mod;
    int len;
    string s;
    vector<int> prefixHash, revHash, basePowers;
    stringHash(int b, int m, string s) : base(b), mod(m), s(s) {
        len = (int) s.length();
        int hash = 0;
        prefixHash.push_back(0);
        for (int i = 0; i < len; i++) {
            hash = (1LL * hash * base) % mod;
            hash = (hash + s[i]) % mod;
            prefixHash.push_back(hash);
        }
        hash = 0;
        revHash.push_back(0);
        for (int i = len-1; i >= 0; i--) {
            hash = (1LL * hash * base) % mod;
            hash = (hash + s[i]) % mod;
            revHash.push_back(hash);
        }
        int pow = 1;
        for (int i = 0; i <= len; i++) { // can be changed to len/2 for optimization
            basePowers.push_back(pow);
            pow = (1LL * pow * base) % mod;
        }
    }
    
    int getHash(int a, int b) { // b is larger than a, the range is [a, b]
        return ((prefixHash[b+1] - 1LL*basePowers[b-a+1]*prefixHash[a]) % mod + mod) % mod;
    }
    int getRevHash(int a, int b) { // b is larger than a the range is [a, b]
        a = len-1-a;
        b = len-1-b;
        return ((revHash[a+1] - 1LL*basePowers[a-b+1]*revHash[b]) % mod + mod) % mod;
    }
    
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, q; cin >> n >> q;
        string s; cin >> s;
        int dp1[n+1];
        int dp2[n+1];
        F0R(i, n) {
            if (i == 0 || s[i] != s[i-1]) {
                dp1[i] = 0;
            } else {
                dp1[i] = dp1[i-1] + 1;
            }

            if (i <= 1 || s[i] != s[i-2]) {
                dp2[i] = 0;
            } else dp2[i] = dp2[i-2]+2;
        }
        stringHash hasher1(101, MOD, s);
        stringHash hasher2(103, 998244353, s);
        while (q--) {
            int l, r; cin >> l >> r;
            l--; r--;
            int len = r-l+1;
            // sum from 2 through l-r+1
            ll ans = 1LL*(len)*(len+1)/2 - 1;
            // check for 2
            bool even = 0;
            bool odd = 0;
            if (len >= 2 && r-dp1[r] <= l) {
                int x = len/2;
                ans -= 1LL*(x+1)*x; // all evens go bye bye
                even = 1;
            }
            if (len >= 3 && r-dp2[r] <= l+1 && r-1-dp2[r-1] <= l+1) {
                odd = 1;
                int x = (len+1)/2;
                ans -= 1LL*x*x;
                ans++;
            }
            if (((len%2)||!even) && (len%2==0||!odd)) {
                if (hasher1.getHash(l, r) == hasher1.getRevHash(l, r) && 
                    hasher2.getHash(l, r) == hasher2.getRevHash(l, r)) {
                    ans -= len;
                }
            }
            cout << ans << nl;
        }
    }
    return 0;
}
