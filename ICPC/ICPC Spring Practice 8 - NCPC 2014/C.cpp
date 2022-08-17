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

typedef pair<ll,ll> pl;

typedef vector<int> vi;
typedef vector<ll> vl;
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
const ll MOD = 360000; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

vi pi(vi s) {
	vi p(sz(s));
	FOR(i,1,sz(s)-1) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vi match(vi s, vi pat) {
	vi pat2 = pat;
    pat2.pb(-1);
    trav(ss, s) pat2.pb(ss);
	vi p = pi(pat2), res;
	FOR(i,sz(p)-sz(s),sz(p)-1)
		if (p[i] == sz(pat)) res.push_back(i - 2 * sz(pat));
	return res;
}

int mod(int x) {
	return (x%MOD + MOD)%MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int a[n]; F0R(i, n) cin >> a[i];
    int b[n]; F0R(i, n) cin >> b[i];
	sort(a, a+n); sort(b, b+n);
    vi c(2*n); F0R(i, n) c[i] = mod(a[(i+1)%n]-a[i]); F0R(i, n) c[i+n] = mod(a[(i+1)%n]-a[i]);
    vi d(n); F0R(i, n) d[i] = mod(b[(i+1)%n]-b[i]);
	vi ret = match(c, d);
	cout <<  (sz(ret) > 0 ? "possible" : "impossible") << nl;
    return 0;
}
