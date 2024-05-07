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

const int MX = 6e5+5;

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

struct FT2 {
	vector<vi> ys; vector<FT> ft;
	FT2(int limx) : ys(limx) {}
    void reset(int limx) {
        ft.clear();
        ys.clear();
        ys.resize(limx);
    }
	void fakeUpdate(int x, int y) {
		for (; x < sz(ys); x |= x + 1) ys[x].push_back(y);
	}
	void init() {
		for (vi& v : ys) sort(all(v)), ft.emplace_back(sz(v));
	}
	int ind(int x, int y) {
		return (int)(lower_bound(all(ys[x]), y) - ys[x].begin()); }
	void update(int x, int y, ll dif) {
        dbg("update", x, y, dif);
		for (; x < sz(ys); x |= x + 1)
			ft[x].update(ind(x, y), dif);
	}
	ll query(int x, int y) {
		ll sum = 0;
		for (; x; x &= x - 1)
			sum += ft[x-1].query(ind(x-1, y));
		return sum;
	}
};

int uniquenessDepth[MX];
string s[MX];
FT2 ft2(MX+5);

struct Trie {
    int uniqueIdx = -1;
    int depth = 0;
    Trie* ch[26] = {0};
    Trie(int d) : depth(d) {}

    void insert(int idx, int j, const string& t) {
        if (depth) {
            if (idx == 5) {
                dbg(depth, uniqueIdx);
            }
            if (uniqueIdx != -1) {
                // update the depth for uniqueIdx
                ft2.update(uniqueIdx, depth, -1);
                assert(uniquenessDepth[uniqueIdx] == depth);
                uniquenessDepth[uniqueIdx]++;
                if (depth+1 <= sz(s[uniqueIdx])+1) {
                    ft2.update(uniqueIdx, depth+1, 1);
                }
            }
            uniqueIdx = idx;
            if (uniquenessDepth[uniqueIdx] == -1) {
                uniquenessDepth[uniqueIdx] = depth;
                ft2.update(uniqueIdx, depth, 1);
            }
        }
        if (j == sz(t)) return;
        int i = t[j]-'a';
        if (ch[i] == 0) {
            ch[i] = new Trie(depth + 1);
        }
        ch[i]->insert(idx, j+1, t);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    FOR(tt, 1, t) {
        cout << "Case #" << tt << ": ";
        int n; cin >> n;
        ft2.reset(n+1);
        F0R(i, n+1) uniquenessDepth[i] = -1;
        F0R(i, n) {
            cin >> s[i+1];
            reverse(all(s[i+1]));
        }
        FOR(i, 1, n) {
            F0R(j, sz(s[i])+2) ft2.fakeUpdate(i, j);
        }
        ft2.init();
        int q; cin >> q;
        vpi qs[n+1];
        while (q--) {
            int a, b, k; cin >> a >> b >> k;
            qs[a].pb({b, k});
        }
        Trie root(0);
        ll ans = 0;
        // go backwards and insert 
        FORd(i, 1, n) {
            dbg("string", i, s[i]);
            // insert the string and upd the uniqunessPtr
            root.insert(i, 0, s[i]);
            ft2.update(i, sz(s[i])+1, -1);
            // query in range for <= k
            trav(p, qs[i]) {
                int tmp = ft2.query(p.f+1, p.s+1);
                dbg(i, p.f, p.s, tmp);
                ans += tmp;
            }
        }
        cout << ans << nl;
    }
    return 0;
}
