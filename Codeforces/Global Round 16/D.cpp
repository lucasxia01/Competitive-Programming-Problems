#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <chrono>
#include <cassert>
#include <climits>

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

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

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

vi compress(vi v) {
    vpi w; F0R(i, sz(v)) w.pb({v[i], i});
    sort(all(w));
    vi ret(sz(v));
    int cnt = 0;
    trav(ww, w) {
        ret[ww.s] = cnt++;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        int a[n*m]; F0R(i, n*m) cin >> a[i];
        vi v; F0R(i, n*m) v.pb(a[i]);
        sort(all(v));
        map<int, int> M;
        int cur = 0;
        F0R(i, n*m) {
            if (i==0 || v[i] != v[i-1]) {
                M[v[i]] = cur++;
            }
        }
        // create a list of indices for each number
        vi g[n*m];
        F0R(i, n*m) {
            v[i] = a[i] = M[a[i]];
            g[a[i]].pb(i);
        }
        // F0R(i, n*m) cout << a[i] << " "; cout << nl;
        int A[n*m];
        int idx = 0;
        F0R(i, n*m) {
            if (sz(g[i]) == 0) break;
            int I = idx;
            int temp = 0;
            cur = 0;
            trav(gg, g[i]) {
                idx++;
                cur++;
                if (idx%m == 0) {
                    reverse(g[i].begin()+temp, g[i].begin()+cur);
                    temp = cur;
                }
            }
            if (temp != cur) {
                reverse(g[i].begin()+temp, g[i].begin()+cur);
            }
            trav(gg, g[i]) {
                A[gg] = I++;
            }
        }
        // F0R(i, n*m) cout << A[i] << " "; cout << nl;
        vi B[n];
        F0R(i, n*m) B[A[i]/m].pb(A[i]);
        ll ans = 0;
        F0R(j, n) {
            FT f(m+5);
            vi h; F0R(i, m) h.pb(B[j][i]);
            h = compress(h);
            // F0R(i, m) cout << h[i] << " "; cout << nl;
            F0R(i, m) {
                ans += f.query(h[i]);
                f.update(h[i], 1);
            }
        }
        cout << ans << nl;
    }
    return 0;
}
