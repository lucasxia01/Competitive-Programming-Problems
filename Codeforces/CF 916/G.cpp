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
const ll MOD = 998244353;
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
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        int n; cin >> n;
        int first[n+1]; FOR(i, 1, n) first[i] = -1;
        vpi a(2*n); 
        F0R(i, 2*n) {
            int x;
            cin >> x;
            a[i].s = i;
            if (first[x] == -1) first[x] = i;
            else {
                a[i].f = first[x];
                a[first[x]].f = i;
            }
        }
        F0R(i, 2*n) {
            dbg(i, a[i].f, a[i].s);
        }
        // need to see what gets hit and then sort out the segments
        RMQ<pi> rmq(a);
        
        int cur = 0;
        ll ans = 1;
        int cnt = 1;
        set<int> s;
        s.insert(-1);
        int num = 0;
        while (1) {
            auto it = s.begin();
            int l = *it;
            if (sz(s) == 1) {
                num++;
                ans = (ans*cnt)%MOD;
                cnt = 2;
                l++;
                if (l == 2*n) break;
                s.erase(s.begin());
                dbg("inserting", l, a[l].f);
                s.insert(l);
                // then process next range
                s.insert(a[l].f);
                continue;
            }
            assert(sz(s) >= 2);
            // get first range and then split it if we can
            it++;
            int r = *it;
            dbg("querying", l+1, r-1);
            if (l+1 == r) {
                s.erase(s.begin());
                continue;
            }
            // range is [l+1, r-1]
            pi p = rmq.query(l+1, r);
            // if its contained, then, this segment sucks
            dbg(p.f, p.s);
            if (p.f < r) {
                s.erase(s.begin());
            } else {
                cnt += 2;
                s.insert(p.f);
                s.insert(p.s);
            }
        }
        cout << num-1 << " " << ans << nl;
    }
    return 0;
}
