#include <bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(v) v.begin(), v.end()
#define sz(v) (int)v.size()
#define sq(a) ((a)*(a))

#define per(i,a,b) for (int i = (b)-1; i >= a; i--)
#define rep(i,a,b) for (int i=a; i<b; i++)

#define FOR(i,a,b) for (int i=a; i<b; i++)
#define F0R(i,a) for (int i=0; i<a; i++)
#define ROF(i,a,b) for (int i = (b)-1; i >= a; i--)
#define R0F(i,a) for (int i = (a)-1; i >= 0; i--)

#define FAST ios::sync_with_stdio(0); cin.tie(0);
#define finish(x) return cout << x << endl, 0;
#define dbg(x) cerr << ">>> " << #x << " = " << x << endl;
#define _ << " _ " <<

#define ll long long

template<class T> bool ckmin(T&a, T&b) { bool B = a > b; a = min(a,b); return B; }
template<class T> bool ckmax(T&a, T&b) { bool B = a < b; a = max(a,b); return B; }

typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ld,ld> pld;
typedef complex<ld> cd;

typedef vector<int> vi;
typedef vector<ld> vld;
typedef vector<vector<int>> vvi;

const ld PI = acos(-1.0);
const ld EPS = 1e-7;
const int MOD = 998244353;

#define int ll

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
	//vector<map<int, int>> s;
  unordered_map<pair<int, int>, int> s;
  int nn;
	FT2(int n) {
    nn = n;
    s = unordered_map<pair<int, int>, int> ();
  }
	void update(int pos, int t, int dif) { // a[pos] += dif
		for (; pos < nn; pos |= pos + 1) s[{pos, t}] += dif;
	}
	ll query(int pos, vi u) { // sum of values in [0, pos)
		ll res = pos;
		for (; pos > 0; pos &= pos - 1) {
      for (auto v : u){
        auto it = s.find({pos - 1, v}); 
        if (it != s.end()){
          // cout << "F " << pos << " " << v << " " << it->second << endl; 
          res -= it->second;
        }
      }
    }
		return res;
	}
	int lower_bound(ll sum, vi u) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= nn){
        int amt = pw;
        for (auto v: u){
          auto it = s.find({pos+pw-1, v});
          if (it != s.end()){
            amt -= it->second;
          }
        }
        if (amt < sum){
				  pos += pw, sum -= amt;
        }
      }
		}
		return pos;
	}
};

/*
struct FT2 {
	vector<map<int, int>> s;
	FT2(int n) : s(n) {}
	void update(int pos, int t, int dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos][t] += dif;
	}
	ll query(int pos, vi u) { // sum of values in [0, pos)
		ll res = pos;
		for (; pos > 0; pos &= pos - 1) {
      for (auto v : u){
        auto it = s[pos-1].find(v); 
        if (it != s[pos-1].end()){
          // cout << "F " << pos << " " << v << " " << it->second << endl; 
          res -= it->second;
        }
      }
    }
		return res;
	}
	int lower_bound(ll sum, vi u) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s)){
        int amt = pw;
        for (auto v: u){
          auto it = s[pos+pw-1].find(v);
          if (it != s[pos+pw-1].end()){
            amt -= it->second;
          }
        }
        if (amt < sum){
				  pos += pw, sum -= amt;
        }
      }
		}
		return pos;
	}
};*/

void solve() {
  int n, q;
  cin >> n >> q;

  vi c(n);
  vector<ll> v(n);

  ll tot = 0;

  FT seg(n);
  FT2 s2(n);
  FT segr(n);
  FT2 s2r(n);

  F0R(i, n) {
    cin >> c[i];
    s2.update(i, c[i], 1);
    s2r.update(n-1-i, c[i], 1);
  }

  F0R(i, n) {
    cin >> v[i];
    tot += v[i];
    seg.update(i, v[i]);
    segr.update(n-i-1, v[i]);
  }

  F0R(i, q){
    int ty;
    cin >> ty;

    if (ty == 1){
      int p, x;
      cin >> p >> x;
      p --;
      s2.update(p, c[p], -1);
      s2r.update(n-1-p, c[p], -1);
      c[p] = x;
      s2.update(p, c[p], 1);
      s2r.update(n-1-p, c[p], 1);
    } else if (ty == 2){
      int p, x;
      cin >> p >> x;
      p --;

      ll diff = x - v[p];

      tot += diff;
      seg.update(p, diff);
      segr.update(n-1-p, diff);
      v[p] += diff;
    } else {
      int x, k;
      cin >> x >> k; x--;

      vector<int> u(k);
      F0R(i, k) cin >> u[i];

      int miss_l = s2.query(x, u);
      int loc_l = s2.lower_bound(miss_l, u);
      ll a_left = seg.query(loc_l + 1);

      int miss_r = s2r.query(n-1-x, u);
      int loc_r = s2r.lower_bound(miss_r, u);
      ll a_right = segr.query(loc_r + 1);

      //cout << tot << " " << miss_l << " " << loc_l << " " << a_left << '\n';
      //cout << tot << " " << miss_r << " " << loc_r << " " << a_right << '\n';
      
      cout << (tot - a_left - a_right) << '\n';
    }
  }

}

int32_t main() { FAST
  int t;
  cin >> t;

  while (t--) solve();

  return 0;
}