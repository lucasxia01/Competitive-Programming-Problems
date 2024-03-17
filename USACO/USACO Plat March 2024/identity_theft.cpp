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

struct Node {
    int depth = 0, cnt = 0;
    Node *c[2];
    Node(int d) {
        depth = d;
        c[0] = c[1] = 0;
    }
};

int ans = 0;

tuple<int, Node*, bool> dfs(Node* cur) {
    // find the best spot to put this dude
    if (cur->c[0] == nullptr && cur->c[1] == nullptr) {
        // then this is a dead end node
        return make_tuple(cur->depth+2, cur, true);
    }
    tuple<int, Node*, bool> ret = make_tuple(INF, nullptr, false);
    if (cur->c[0] == nullptr) {
        ckmin(ret, make_tuple(cur->depth+1, cur, false));
    } else {
        ckmin(ret, dfs(cur->c[0]));
    }
    if (cur->c[1] == nullptr) {
        ckmin(ret, make_tuple(cur->depth+1, cur, false));
    } else {
        ckmin(ret, dfs(cur->c[1]));
    }
    return ret;

}
using pq = priority_queue<tuple<int, Node*, bool>>;
map<Node*, pq> m;

void solve(Node* cur) {
    if (m.count(cur)) {
        return;
    }
    // otherwise calculate m[cur]
    if (!cur->c[0] && !cur->c[1]) {
        m[cur] = pq();
        m[cur].push({-cur->depth-2, cur, 1});
        return;
    }
    pq curpq;
    if (cur->c[0]) solve(cur->c[0]);
    else {
        curpq.push({-cur->depth-1, cur, 0});
    }
    if (cur->c[1]) solve(cur->c[1]);
    else {
        curpq.push({-cur->depth-1, cur, 0});
    }
    int sz0 = (cur->c[0] == nullptr?0:sz(m[cur->c[0]]));
    int sz1 = (cur->c[1] == nullptr?0:sz(m[cur->c[1]]));
    if (sz0+sz1 == 0) {
        m[cur] = curpq;
    } else if (sz0 >= sz1) {
        swap(m[cur], m[cur->c[0]]);
        while(!m[cur->c[1]].empty()) {
            auto t = m[cur->c[1]].top(); m[cur->c[1]].pop();
            m[cur].push(t);
        }
    } else {
        swap(m[cur], m[cur->c[1]]);
        while(!m[cur->c[0]].empty()) {
            auto t = m[cur->c[0]].top(); m[cur->c[0]].pop();
            m[cur].push(t);
        }
    }
    while (!curpq.empty()) {
        auto t = curpq.top(); curpq.pop();
        m[cur].push(t);
    }

    // dbg(cur->s);
    // pq tmp = m[cur];
    // while (!tmp.empty()) {
    //     auto t = tmp.top(); tmp.pop();
    //     assert(get<0>(t) <= 0);
    //     // dbg(-get<0>(t), get<1>(t)->s, get<2>(t));
    // }
}

void insert(Node* root, string s) {
    Node* cur = root;
    for (int i = 0; i < s.size(); i++) {
        dbg(s, s[i]);
        cur->cnt++;
        if (cur->c[s[i]-'0'] == nullptr) {
            cur->c[s[i]-'0'] = new Node(cur->depth+1);
        }
        cur = cur->c[s[i]-'0'];
    }
    cur->cnt++;
    // if this node already existed before 
    if (cur->cnt > 1) {
        dbg("prefix", s);
        // we need to handle this
        // try dfsing from this node to find the cheapest position
        solve(cur);
        tuple<int, Node*, bool> t = m[cur].top(); m[cur].pop();
        int tmp = -get<0>(t)-(cur->depth);
        // dbg(-get<0>(t), get<1>(t)->s, get<2>(t), cur->depth);
        ans += tmp;
        Node* other = get<1>(t);
        if (get<2>(t)) {
            // we need to extend the node
            assert(other->c[0] == nullptr && other->c[1] == nullptr);
            other->c[0] = new Node(other->depth+1);
            other->c[1] = new Node(other->depth+1);
            m[cur].push({-other->depth-3, other->c[0], 1});
            m[cur].push({-other->depth-3, other->c[1], 1});
        } else {
            assert(other->c[0] != nullptr || other->c[1] != nullptr);
            if (!other->c[0]) {
                other->c[0] = new Node(other->depth+1);
                m[cur].push({-other->depth-3, other->c[0], 1});
            } else {
                other->c[1] = new Node(other->depth+1);
                m[cur].push({-other->depth-3, other->c[1], 1});

            }
            assert(other->c[0] != nullptr && other->c[1] != nullptr);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    string s[n]; F0R(i, n) cin >> s[i];
    Node* root = new Node(0);
    vpi v; F0R(i, n) v.pb({sz(s[i]), i});
    sort(all(v));
    reverse(all(v));
    F0R(i, n) insert(root, s[v[i].s]);
    cout << ans << nl;
    return 0;
}