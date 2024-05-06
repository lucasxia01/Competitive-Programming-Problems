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

const int MX = 3e5+5;

int qCnt = 0;
int n;
int query(int x, int y) {
    if (qCnt == 2*n) while (1);
    qCnt++;
    cout << "? " << x+1 << " " << y+1 << endl;
    cout.flush();
    int ret; cin >> ret;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        qCnt = 0;
        cin >> n;
        if (n == -1) return 1;
        
        vi v; 
        if (n <= 4) {
            F0R(i, n) {
                v.pb(i);
            }
        } else {
            while (1) {
                int a = rng()%n, b = rng()%n;
                if (a == b) continue;
                int ret = query(a, b);
                if (ret == -1) return 1;
                else if (ret > 1) {
                    v.pb(a);
                    break;
                }
            }
            F0R(i, n) {
                if (i != v[0]) v.pb(i);
            }
        }
        while (sz(v) > 2) {
            int cur = v[0];
            vi nxt; int hi = -1;
            trav(i, v) {
                if (cur != i) {
                    int ret = query(cur, i);
                    if (ret == -1) return 1;
                    if (ckmax(hi, ret)) {
                        nxt.clear();
                    }
                    if (hi == ret) nxt.pb(i);
                }
            }
            if (sz(nxt) == 1) nxt.pb(cur);
            v = nxt;
        }
        if (sz(v) == 0) assert(0);
        else if (sz(v) == 1) cout << "! " << v[0]+1 << " " << v[0]+1 << nl;
        else cout << "! " << v[0]+1 << " " << v[1]+1 << nl;
        cout.flush();
        int x; cin >> x;
        if (x == -1) return 1;
    }
    return 0;
}
