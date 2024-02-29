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
    int t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        string s; cin >> s;
        vi sufPos;
        F0R(i, n) if (s[i] == '<') sufPos.pb(i);
        sufPos.pb(n);
        int m = sz(sufPos);
        ll sufSum[m+1]; sufSum[0] = 0;
        F0R(i, m) sufSum[i+1] = sufSum[i]+sufPos[i];
        vi prePos; prePos.pb(-1);
        vl prefSum; prefSum.pb(0);
        prefSum.pb(-1);
        int sufPtr = 0;
        F0R(i, n) {
            if (s[i] == '>') {
                prePos.pb(i);
                prefSum.pb(prefSum.back()+i);
            }
            // see which side has more
            int len = min(m-sufPtr, sz(prePos));
            bool side = 0;
            if (s[i] == '>') {
                side = ((m-sufPtr >= sz(prePos))?1:0);
            } else {
                side = ((m-sufPtr <= sz(prePos))?0:1);
            }
            // we want the sum of last len elem of prefPos
            // and sum of first len elem of sufPos starting from sufPtr
            ll ans = 0;
            int l = sz(prefSum)-1;
            if (s[i] == '>' && side == 0) {
                ll v1 = prefSum[l]-prefSum[l-len];
                ll v2 = sufSum[sufPtr+len]-sufSum[sufPtr];
                ans = 2*(v2-v1);
                ans -= n;
                ans += i;
            } else if (s[i] == '>' && side == 1) {
                ll v1 = prefSum[l]-prefSum[l-len];
                ll v2 = sufSum[sufPtr+len-1]-sufSum[sufPtr];
                ans = 2*(v2-v1);
                ans += i-1;
            } else if (s[i] == '<' && side == 0) {
                ll v1 = prefSum[l]-prefSum[l-len+1];
                ll v2 = sufSum[sufPtr+len]-sufSum[sufPtr];
                ans = 2*(v2-v1);
                ans -= n+i;
            } else {
                ll v1 = prefSum[l]-prefSum[l-len];
                ll v2 = sufSum[sufPtr+len]-sufSum[sufPtr];
                ans = 2*(v2-v1);
                ans -= i;
                ans += -1;
            }
            cout << ans << ' ';
            if (s[i] == '<') {
                sufPtr++;
            }
        }
        cout << nl;
    }
    return 0;
}
