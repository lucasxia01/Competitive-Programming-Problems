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
const int sum_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool cksum(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

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

const int MX = 4e5+5;

vl cnt[MX];
vl a[MX];

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, madd = 0, val = 0;
    int sum(int a, int b) {
        return a+b;
    }
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of 0
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = sum(l->val, r->val);
		}
		else val = v[lo];
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return val;
		push();
		return sum(l->query(L, R), r->query(L, R));
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = sum(l->val, r->val);
		}
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

vpi q[MX];
int ptr[MX];
vi v[MX];
Node st(0, MX);

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    FOR(i, 1, MX-1) {
        for (int j = i; j <= MX-1; j+=i) cnt[j].pb(i);
    }
    FOR(i, 1, MX-1) {
        if (i%2 == 0) {
            int n = sz(cnt[i]); n-=2;
            int j = 0, k = n-1;
            a[i].pb(0);
            while (j < k) {
                while (j < k && cnt[i][j] + cnt[i][k] > i/2) {
                    k--;
                }
                a[i].pb(a[i].back()+n-1-k);
                j++;
            }
            while (j < n) {
                a[i].pb(a[i].back()+n-1-j);
                j++;
            }
            a[i].pb(a[i].back());
            a[i].pb(a[i].back());
        }
    }
    int t; cin >> t;
    int ans[t];
    F0R(i, t) {
        int l, r; cin >> l >> r;
        q[l].pb({r, i});
    }
    F0R(i, MX) ptr[i] = sz(cnt[i]);
    FORd(l, 1, MX-1) {
        for (int k = (MX-1)/l * l; k >= l; k-=l) {
            // update 
            ptr[k]--;
            if (k%2 == 0) {
                st.add(k/2, k/2+1, a[k][ptr[k]+1]-a[k][ptr[k]]);
            }
            if (k >= MX/2) continue;
            st.add(k, k+1, max((ll)0, sz(cnt[k])-ptr[k]-2));
            
        }
        trav(p, q[l]) {
            ll T = (p.f-l+1);
            ll sum = T*(T-1)*(T-2)/6;
            ans[p.s] = sum-st.query(0, p.f+1);
        }
    }
    F0R(i, t) cout << ans[i] << nl;
    return 0;
}
