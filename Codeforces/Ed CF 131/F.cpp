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

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(...) dbg_out(__VA_ARGS__);
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){
	c << "(" << v.f << "," <<v.s <<")"; return c;
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

const int MX = 2e5+5;

struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, madd = 0, sum = 0, v = 0;
	Node(int lo,int hi):lo(lo),hi(hi){}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) {
            if (lo+1==hi) return sum*v;
            return sum;
        }
		push();
		int ret = l->query(L, R) + r->query(L, R);
        return ret;
	}
    int set(int L) {
        int R = L+1;
        int ret = 0;
		if (R <= lo || hi <= L) {
            if (lo+1==hi) ret = sum*v;
            else ret = sum;
        } else {
            if (L <= lo && hi <= R) { // should be a leaf
                v = !v;
                ret = sum * v;
            }
            else {
                push();
                int x = l->set(L), y = r->set(L);
                v = l->v + r->v;
                sum = x+y;
                ret = sum;
            }
        }
        return ret;
	}
	int add(int L, int R, int x) {
        int ret = 0;
		if (R <= lo || hi <= L) {
            if (lo+1==hi) ret = sum*v;
            else ret = sum;
        } else {
            if (L <= lo && hi <= R) {
                madd += x;
                if (lo+1 == hi) {
                    sum += x;
                    ret = sum*v;
                } else {
                    sum += x*v;
                    ret = sum;
                }
            }
            else {
                push();
                int t1 = l->add(L, R, x), t2 = r->add(L, R, x);
                sum = t1+t2;
                ret = sum;
            }
        }
        return ret;
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

int a[MX];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int q, d; cin >> q >> d;
    Node* tr = new Node(0, MX);
    ll ans = 0;
    F0R(i, q) {
        int x; cin >> x;
        a[x] = !a[x];
        if (a[x]) tr->set(x);
        else tr->add(x-d, x, -1);
        
        int cnt = tr->query(x, x+1);
        int w = tr->query(x-d, x);
        ll val = w + cnt*(cnt-1)/2;
        // F0R(j, 9) cerr << tr->query(j, j+1) << " "; cout << nl;
        dbg(w, cnt, val);
        if (a[x]) ans += val;
        else ans -= val;
        if (a[x]) tr->add(x-d, x, 1);
        else tr->set(x);

        cout << ans << nl;
    }
    return 0;
}
