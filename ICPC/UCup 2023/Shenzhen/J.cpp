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
    int t; cin >> t;
    while (t--) {
        int x, y, A, B; cin >> x >> y >> A >> B;
        bool swapped = 0;
        if (x > y) {
            swap(x, y);
            swap(A, B);
            swapped = 1;
        }
        // brute force over all sqrt(x) and sqrt(y) possible bases
        map<vi, int> v_x, v_y;
        int i = 2;
        for (; i*i <= x; i++) {
            // convert x to base i
            vi cur;
            int X = x;
            while (X) {
                cur.pb(X%i);
                X /= i;
            }
            v_x[cur] = i;
        }
        int j = 2;
        for (; j*j <= y; j++) {
            // convert y to base j
            vi cur;
            int Y = y;
            while (Y) {
                cur.pb(Y%j);
                Y /= j;
            }
            v_y[cur] = j;
        }
        // check if there's a match between these two
        pi ans = {-1, -1};
        trav(v, v_x) {
            if (v_y.count(v.f)) {
                if (v.s <= A && v_y[v.f] <= B) {
                    ans = {v.s, v_y[v.f]};
                    break;
                }
            }
        }
        // now do the case where we have 1 digit between the two
        if (x == y) {
            int b = y+1;
            assert(b >= 2);
            if (b <= A && b <= B) {
                ans = {b, b};
            }
        }
        // now do the case of 2 digits
        // base for x has to be in [i, A]
        // base for y has to be in [j, B]
        int diff = y-x;
        if (diff == 0) {
            ans.f = ans.s = 2;
        } else {
            // try all divisors
            for (int k = 1; k*k <= diff; k++) {
                if (diff % k) continue;
                // divisors are k and diff/k
                // 2nd digit is k
                // a > k
                // 0 < x - k*a < a
                // (k+1)*a > x
                // a > x/(k+1)
                dbg(diff, k);
                int dig = k; // dig is the "tens" digit
                int a = max(x/(dig+1), dig)+1;
                int b = a+diff/dig;
                if (x-dig*a >= 0 && a >= i && a <= A && b >= j && b <= B) {
                    ans = {a, b};
                    break;
                }
                // now try it with 2nd digit being diff/k
                dig = diff/k;
                a = max(x/(dig+1), dig)+1;
                b = a+diff/dig;
                if (x- dig*a >= 0 && a >= i && a <= A && b >= j && b <= B) {
                    ans = {a, b};
                    break;
                }
            }
        }

        // the bases are between 
        if (ans.f == -1) cout << "NO" << nl;
        else {
            cout << "YES" << nl;
            assert(min(ans.f, ans.s) >= 2);
            assert(ans.f <= A && ans.s <= B);
            if (swapped) swap(ans.f, ans.s);
            cout << ans.f << " " << ans.s << nl;
        }
    }
    return 0;
}
