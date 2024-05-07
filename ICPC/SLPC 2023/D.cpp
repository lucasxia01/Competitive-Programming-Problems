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
    ll d_km; int n; cin >> d_km >> n;
    ll d_kms_per_h = d_km * 3600;
    // womais just drives in same lane until next event
    vector<array<int, 4>> events;
    set<pi> left;
    F0R(i, n) {
        int t, m; char c; cin >> t >> m >> c;
        if (c == 'R') events.pb({t, m, 1, 0});
        else {
            int s; cin >> s;
            events.pb({t, m, 0, s});
        }
    }
    // start in right lane and go crazy
    ll curDist_kms_per_h = 0;
    const ll rSpeed_km_per_h = 100;
    ll curSpeed_km_per_h = rSpeed_km_per_h;
    ll prevTime_s = 0;
    ll ans = -1;
    map<int, int> speeds;
    trav(e, events) {
        int t_s = e[0];
        int idx = e[1];
        dbg(curDist_kms_per_h, curSpeed_km_per_h, prevTime_s, t_s, d_kms_per_h);
        if (curDist_kms_per_h + (t_s-prevTime_s)*curSpeed_km_per_h >= d_kms_per_h) {
            ans = prevTime_s + (d_kms_per_h-curDist_kms_per_h) / curSpeed_km_per_h;
            if (curDist_kms_per_h + (ans-prevTime_s)*curSpeed_km_per_h < d_kms_per_h) ans++;
            assert(curDist_kms_per_h + (ans-1-prevTime_s)*curSpeed_km_per_h < d_kms_per_h);
            assert(curDist_kms_per_h + (ans-prevTime_s)*curSpeed_km_per_h >= d_kms_per_h);
            break;
        }
        curDist_kms_per_h += (t_s-prevTime_s)*curSpeed_km_per_h;
        if (e[2] == 1) {
            // remove from set
            left.erase({speeds[e[1]], e[1]});
        } else {
            // add to set
            left.insert({e[3], e[1]});
            speeds[e[1]] = e[3];
        }
        prevTime_s = t_s;
        if (sz(left) && left.begin()->f > 100) {
            curSpeed_km_per_h = left.begin()->f;
        } else {
            curSpeed_km_per_h = rSpeed_km_per_h;
        }
        dbg(curSpeed_km_per_h);
    }
    if (ans == -1) {
        ans = prevTime_s + (d_kms_per_h-curDist_kms_per_h) / curSpeed_km_per_h;
        if (curDist_kms_per_h + (ans-prevTime_s)*curSpeed_km_per_h < d_kms_per_h) ans++;
        assert(curDist_kms_per_h + ((ans-1)-prevTime_s)*curSpeed_km_per_h < d_kms_per_h);
        assert(curDist_kms_per_h + (ans-prevTime_s)*curSpeed_km_per_h >= d_kms_per_h);
    }
    cout << ans << nl;
    return 0;
}
