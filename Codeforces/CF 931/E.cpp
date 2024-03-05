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
        int n; cin >> n;
        vector<array<int, 3>> ans;
        if (n == 3) {
            ans.pb({1, 2, 3});
        } else if (n == 4) {
            ans.pb({1, 3, 4});
        } else if (n == 5) {
            ans.pb({3, 4, 5});
        } else if (n == 6) {
            ans.pb({2, 4, 6});
            ans.pb({1, 3, 5});
        } else if (n == 7) {
            ans.pb({1, 3, 4});
            ans.pb({5, 6, 7});
        } else if (n == 8) {
            ans.pb({5, 6, 7});
            ans.pb({1, 3, 8});
        } else if (n == 9) {
            ans.pb({7, 8, 9});
            ans.pb({1, 5, 6});
        } else if (n == 10) {
            ans.pb({7, 8, 9});
            ans.pb({2, 6, 10});
        } else if (n == 11) {
            ans.pb({9, 10, 11});
            ans.pb({5, 6, 7});
            ans.pb({1, 3, 8});
        } else if (n == 12) {
            ans.pb({7, 8, 9});
            ans.pb({1, 11, 12});
            ans.pb({2, 6, 10});
            ans.pb({3, 4, 5});
        }
        if (n > 12) {
            // bottom half is ignore lol
            // split the top half [n/2, n] into chunks of 12
            int half = (n+1)/2;
            int i = n;
            int used = 0;
            if (n%4 == 0) {
                // do i-1, i, i+1
                ans.pb({1, n-1, n});
                i-=2;
                used = 2;
            } else if (n%4 == 3) {
                ans.pb({1, 2, n});
                i--;
                used = 1;
            }
            while (i >= half) {
                // we can handle this now
                i-=11;
                assert(i > used);
                if (i%4 == 2) {
                    // we want {3, 4, 5}, {7, 8, 9}, {11, 12, 13}, {2, 6, 10}
                    ans.pb({i+1, i+2, i+3});
                    ans.pb({i+5, i+6, i+7});
                    ans.pb({i+9, i+10, i+11});
                    ans.pb({i, i+4, i+8});
                } else if (i%4 == 3) {
                    // we want {3, 4, 5}, {7, 8, 9}, {11, 12, 13}, {6, 10, 14}
                    ans.pb({i, i+1, i+2});
                    ans.pb({i+4, i+5, i+6});
                    ans.pb({i+8, i+9, i+10});
                    ans.pb({i+3, i+7, i+11});
                } else assert(0);
                i--;
            }
        }
        cout << sz(ans) << nl;
        trav(x, ans) {
            cout << x[0] << " " << x[1] << " " << x[2] << nl;
        }
    }
    return 0;
}
