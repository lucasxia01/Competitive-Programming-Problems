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

const int MX = 5001 * 1000 + 5;

struct Circle {
    int x, y;
    int l, r;
};

ll dist(int x1, int y1, int x2, int y2) {
    return 1LL*(x1-x2)*(x1-x2) + 1LL*(y1-y2)*(y1-y2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int r, c, d, n; cin >> r >> c >> d >> n;
    Circle a[n];
    vpi v;
    set<pi> s;
    F0R(i, n) {
        int x, y; cin >> x >> y; x--; y--;
        v.pb({x, y});
        s.insert({x, y});
    }
    sort(all(v));
    F0R(i, n) {
        int x = v[i].f;
        int y = v[i].s;
        a[i] = {x, y, y, y-1};
    }
    if (r > MX || c > MX) {
        cout << 0 << nl;
        return 0;
    }
    // initialize at row -d-1
    int cnt[c]; F0R(i, c) cnt[i] = 0;
    int ptr = 0;
    int ans = n+1;
    queue<Circle> q; // see what circles are alive now
    FOR(i, -d, r-1) {
        // add things to the queue that start at row i
        while (ptr < n && a[ptr].x-d == i) {
            q.push(a[ptr]);
            ptr++;
        }
        // now traverse the queue
        queue<Circle> other_q;
        while (!q.empty()) {
            Circle cur = q.front();
            dbg("circle", cur.x, cur.y, cur.l, cur.r);
            q.pop();
             // check if (i, l) is in circle
            while (cur.l > 0 && dist(i, cur.l-1, cur.x, cur.y) <= 1LL*d*d) {
                cur.l--;
                cnt[cur.l]++;
            }
            while (cur.l < cur.y && dist(i, cur.l, cur.x, cur.y) > 1LL*d*d) {
                cnt[cur.l]--;
                dbg("decrement", cur.l);
                cur.l++;
            }
            // check if (i, r) is in circle
            while (cur.r < c-1 && dist(i, cur.r+1, cur.x, cur.y) <= 1LL*d*d) {
                cur.r++;
                cnt[cur.r]++;
            }
            while (cur.r >= cur.y && dist(i, cur.r, cur.x, cur.y) > 1LL*d*d) {
                cnt[cur.r]--;
                dbg("decrement", cur.r);
                cur.r--;
            }
            dbg("circle after row", i, cur.x, cur.y, cur.l, cur.r);
            other_q.push(cur);
        }
        q = other_q;
        // remove things that ended here above us
        while (!q.empty() && q.front().x+d == i-1) {
            q.pop();
        }
        // count answer if its above 0
        dbg(i, sz(q));
        dbg_array(cnt, c);
        if (false) {
            F0R(j, c) if (!s.count({i, j})) ckmin(ans, cnt[j]);
        } else if (i >= 0) {
            vpi V;
            int N = sz(q);
            F0R(j, N) {
                Circle cur = q.front(); q.pop();
                q.push(cur);
                V.pb({cur.l, 1});
                V.pb({cur.r+1, -1});
            }
            sort(all(V));
            int tmp = 0;
            bool crossed0 = 0;
            F0R(j, sz(V)) {
                tmp += V[j].s;
                if (j == sz(V)-1 || V[j].f != V[j+1].f) {
                    if (!s.count({i, V[j].f}) && V[j].f >= 0 && V[j].f < c) ckmin(ans, tmp);
                }
            }
        }
        
    }
    // now also try sitting next to all the students and i, 0 for all i
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    F0R(dir, 4) {
        trav(u, v) {
            int x = u.f + dx[dir];
            int y = u.s + dy[dir];
            if (x < 0 || x >= r || y < 0 || y >= c) continue;
            if (s.count({x, y})) continue;
            // count how many dudes you can here
            int tmp = 0;
            trav(o, v) {
                if (dist(x, y, o.f, o.s) <= 1LL*d*d) tmp++;
            }
            ckmin(ans, tmp);
        }
    }
    F0R(i, r) {
        int x = i;
        int y = 0;
        if (x < 0 || x >= r || y < 0 || y >= c) continue;
        if (s.count({x, y})) continue;
        // count how many dudes you can here
        int tmp = 0;
        trav(o, v) {
            if (dist(x, y, o.f, o.s) <= 1LL*d*d) tmp++;
        }
        ckmin(ans, tmp);
    }
    cout << ans << nl;
    return 0;
}
