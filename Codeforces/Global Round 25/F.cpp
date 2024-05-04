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

struct FT {
    vi f;
    int n;
    FT(int n) : f(n+1, 0) { this->n = n+1; }

    void add(int i, int x) {
        i++;
        while (i < n) {
            f[i] += x;
            i += (i&-i);
        }
    }
    ll query(int i) {
        i++;
        ll ret = 0;
        while (i > 0) {
            ret += f[i];
            i -= (i&-i);
        }
        return ret;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        int p[n], pos[n];
        F0R(i, n) {
            cin >> p[i];
            p[i]--;
            pos[p[i]] = i;
        }
        FT f(n);
        int inv[n];
        int cur = 0;
        F0R(i, n) {
            int cnt = f.query(pos[i]); // counts how many things below it are in front of it
            inv[i] = i-cnt;
            f.add(pos[i], 1);
            cur += inv[i];
            dbg("inversions of", i, "with things lower:", inv[i], i, cnt);
        }
        dbg("total", cur);
        ll hi = 1LL*n*(n-1)-cur;
        if (k > hi || k < cur || (k-cur)%2) {
            cout << "NO" << nl;
            continue;
        }
        cout << "YES" << nl;
        int q[n]; F0R(i, n) q[i] = -1;
        // now move i to the back
        if (cur == k) {
            F0R(i, n) q[i] = i;
        } else {
            F0R(i, n) {
                // i moves to n-1-ith position from 0th position
                // we want to count how many inversions n-1-i has with stuff lower than it
                int gain = (n-1-i-inv[n-1-i])*2;
                dbg(n-1-i, inv[n-1-i], gain);
                if (cur+gain >= k) {
                    // we stop here and find which one is best
                    dbg(i, cur, gain);
                    dbg_array(q, n);
                    int cnt = 0;
                    F0Rd(j, n-1-i) {
                        if (pos[j] < pos[n-1-i]) {
                            cnt++;
                            if (cur+2*cnt == k) {
                                dbg(j);
                                q[n-1-i] = i+j;
                                // set the first j+1 things
                                FOR(jj, j, n-1-i-1) q[jj] = jj+i+1;
                                F0R(jj, j) q[jj] = i+jj;
                                break;
                            }
                        }
                    }
                    cur += 2*cnt;
                    break;
                }
                cur += gain;
                q[n-1-i] = i;
            }
        }
        assert(cur == k);
        dbg_array(q, n);
        F0R(i, n) cout << q[i]+1 << " "; cout << nl;
    }
    return 0;
}
