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

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(...) dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

vector<string> v;
int n, m;

int dx[5] = {0, 0, 1, -1, 0};
int dy[5] = {1, -1, 0, 0, 0};
struct State {
    int x, y, t;
    bool isValid() {
        if (x == 0 && y == 1) return 1;
        else if (x == n-1 && y == m-2) return 1;
        if (x < 1 || x >= n-1 || y < 1 || y >= m-1) return 0;
        int X = x-1, Y = y-1;
        int N = n-2, M = m-2;
        if (v[(X-(t%N)+N)%N+1][Y+1] == 'v') return 0;
        if (v[(X+(t%N)+N)%N+1][Y+1] == '^') return 0;
        if (v[X+1][(Y-(t%M)+M)%M+1] == '>') return 0;
        if (v[X+1][(Y+(t%M)+M)%M+1] == '<') return 0;
        return 1;
    }

    bool operator<(const State& o) const {
        return tie(x, y, t) < tie(o.x, o.y, o.t);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    while (!cin.eof()) {
        string s; cin >> s; v.pb(s);
    }
    n = sz(v), m = sz(v[0]);
    queue<State> q;
    q.push({0, 1, 0});
    set<State> s;
    State end;
    while (!q.empty()) {
        State cur = q.front(); q.pop();
        // dbg(cur.x, cur.y, cur.t, cur.isValid());
        if (s.count(cur)) continue;
        if (!cur.isValid()) continue;
        s.insert(cur);

        if (cur.x == n-1 && cur.y == m-2) {
            end = cur;
            break;
        }
        F0R(d, 5) {
            int nx = cur.x+dx[d], ny = cur.y+dy[d];
            q.push({nx, ny, cur.t+1});
        }
    }
    while (!q.empty()) q.pop();
    s.clear();
    q.push(end);
    dbg(end.t);
    while (!q.empty()) {
        State cur = q.front(); q.pop();
        // dbg(cur.x, cur.y, cur.t, cur.isValid());
        if (s.count(cur)) continue;
        if (!cur.isValid()) continue;
        s.insert(cur);

        if (cur.x == 0 && cur.y == 1) {
            end = cur;
            break;
        }
        F0R(d, 5) {
            int nx = cur.x+dx[d], ny = cur.y+dy[d];
            q.push({nx, ny, cur.t+1});
        }
    }
    while (!q.empty()) q.pop();
    s.clear();
    q.push(end);
    dbg(end.t);
    while (!q.empty()) {
        State cur = q.front(); q.pop();
        // dbg(cur.x, cur.y, cur.t, cur.isValid());
        if (s.count(cur)) continue;
        if (!cur.isValid()) continue;
        s.insert(cur);

        if (cur.x == n-1 && cur.y == m-2) {
            end = cur;
            break;
        }
        F0R(d, 5) {
            int nx = cur.x+dx[d], ny = cur.y+dy[d];
            q.push({nx, ny, cur.t+1});
        }
    }
    cout << end.t << nl;
    return 0;
}
