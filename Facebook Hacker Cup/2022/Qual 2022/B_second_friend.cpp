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
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){
	c << "(" << v.fi << "," <<v.se <<")"; return c;
}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){
	out << "{ ";
	trav(x,c) out<<x<<" ";
	out<<"}"; return out;
}
#else
#define dbg(...)
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3005;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int cnt[MX][MX];
void solve() {
    int n, m; cin >> n >> m;
    string a[n]; F0R(i, n) cin >> a[i];
    // now just fill everything
    queue<pi> q;
    F0R(i, n) F0R(j, m) {
        cnt[i][j] = 0;
        if (a[i][j] == '#') continue;
        int c = 0;
        F0R(d, 4) {
            int nx = i+dx[d], ny = j+dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || a[nx][ny] == '#') continue;
            c++;
        }
        if (c == 1) q.push({i, j});
        cnt[i][j] = c;
    }
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        F0R(d, 4) {
            int nx = x+dx[d], ny = y+dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || a[nx][ny] == '#') continue;
            if (cnt[nx][ny] == 2) q.push({nx, ny});
            if (cnt[nx][ny]) cnt[nx][ny]--;
        }
    }
    bool ok = 1;
    F0R(i, n) F0R(j, m)  {
        if (a[i][j] == '^' && cnt[i][j] < 2) ok = 0;
    }
    cout << (ok?"Possible": "Impossible") << nl;
    if (ok) {
        F0R(i, n) {
            F0R(j, m) {
                if (a[i][j] != '.') cout << a[i][j];
                else {
                    if (cnt[i][j] < 2) cout << '.';
                    else cout << '^';
                }
            }
            cout << nl;
        }
    }
    cout.flush();
    fflush(stdout);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    FOR(i, 1, t) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
