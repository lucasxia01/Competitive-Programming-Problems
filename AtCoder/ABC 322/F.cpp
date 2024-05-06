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
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

struct Data {
    bool all = 0;
    bool valid = 1;
    bool leftBit = 0, rightBit = 0;
    int leftRun = 0, rightRun = 0;
    int run0 = 0, run1 = 0;
};

Data merge(const Data& a, const Data& b) {
    if (!a.valid) return b;
    if (!b.valid) return a;
    Data ret = a;
    ret.rightBit = b.rightBit;
    if (a.all && a.leftBit == b.leftBit) {
        ret.leftRun += b.leftRun;
    } 
    ret.rightRun = b.rightRun;
    if (b.all && b.rightBit == a.rightBit) {
        ret.rightRun += a.rightRun;
    }
    ret.run0 = max(a.run0, b.run0);
    ret.run1 = max(a.run1, b.run1);
    if (a.rightBit == b.leftBit) {
        if (a.rightBit == 0) ckmax(ret.run0, a.rightRun + b.leftRun);
        else ckmax(ret.run1, a.rightRun + b.leftRun);
    }
    ret.all = (a.all && b.all && a.leftBit == b.rightBit);
    return ret;
} 

const int inf = 1e9;

struct Node {
    int lo, hi;
	Node *l = 0, *r = 0;
	bool minv = 0;
    
    Data val;

	Node(const string& s, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(s, lo, mid); r = new Node(s, mid, hi);
			val = merge(l->val, r->val);
		}
		else {
            val.all = 1;
            val.leftBit = val.rightBit = (s[lo] == '1');
            val.leftRun = val.rightRun = 1;
            val.run0 = (s[lo] == '0');
            val.run1 = (s[lo] == '1');
        }
	}

	Data query(int L, int R) {
		if (R <= lo || hi <= L) {
            Data bad; bad.valid = 0;
            return bad;
        }
		if (L <= lo && hi <= R) return val;
		push();
		return merge(l->query(L, R), r->query(L, R));
	}
	void inv(int L, int R) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			minv = !minv;
			val.leftBit = !val.leftBit;
            val.rightBit = !val.rightBit;
            swap(val.run0, val.run1);
		}
		else {
			push(), l->inv(L, R), r->inv(L, R);
			val = merge(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
            assert(0);
		}
		if (minv)
			l->inv(lo,hi), r->inv(lo,hi), minv = 0;
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    dbg(sizeof(Node));
    int n, q; cin >> n >> q;
    string s; cin >> s;
    Node* st = new Node(s, 0, n);
    while (q--) {
        int c, L, R; cin >> c >> L >> R;
        L--;
        if (c == 1) {
            st->inv(L, R);
        } else {
            Data ret = st->query(L, R);
            cout << ret.run1 << nl;
        }
    }
    return 0;
}
