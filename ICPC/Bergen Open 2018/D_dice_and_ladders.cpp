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
const int SZ = 64;

double add(double a, double b)
{
	return a+b;
}

double mult(double a, double b)
{
	return a*b;
}

struct matrix
{
	double arr[SZ][SZ];

	void reset()
	{
		F0R(i, SZ) F0R(j, SZ) arr[i][j] = 0;
	}

	void makeiden()
	{
		reset();
		for(int i=0;i<SZ;i++)
		{
			arr[i][i] = 1;
		}
	}

	matrix operator + (const matrix &o) const 
	{
		matrix res;
		for(int i=0;i<SZ;i++)
		{
			for(int j=0;j<SZ;j++)
			{
				res.arr[i][j] = add(arr[i][j], o.arr[i][j]);
			}
		}
		return res;
	}

	matrix operator * (const matrix &o) const 
	{
		matrix res;
		for(int i=0;i<SZ;i++)
		{
			for(int j=0;j<SZ;j++)
			{
				res.arr[i][j] = 0;
				for(int k=0;k<SZ;k++)
				{
					res.arr[i][j] = add(res.arr[i][j] , mult(arr[i][k] , o.arr[k][j]));
				}
			}
		}
		return res;
	}
};

matrix power(matrix a, int b)
{
	matrix res;
	res.makeiden();
	while(b)
	{
		if(b & 1)
		{
			res = res * a;
		}
		a = a * a;
		b >>= 1;
	}
	return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int r, c, k; cin >> r >> c >> k;
    ld p; cin >> p;
    int n = r*c;
    matrix m; m.reset();
	int l[SZ]; F0R(i, SZ) l[i] = -1;
	F0R(i, k) {
		int a, b; cin >> a >> b; a--; b--;
		l[a] = b;
	}
    F0R(i, n) {
		F0R(j, 6) {
			int ni = i+j+1;
			if (ni >= n) m.arr[n-1][i] += ((ld)1.0)/6;
			else if (l[ni] == -1) m.arr[ni][i] += ((ld)1.0)/6;
			else m.arr[l[ni]][i] += ((ld)1.0)/6;
		}
    }
	// matrix x = power(m, 2);
	// F0R(i, n) {
	// 	F0R(j, n) cout << x.arr[i][j] << " ";
	// 	cout << nl;
	// } cout << nl;
	int lo = 0, hi = 1e8;
	while (lo < hi) {
		int mid = (lo+hi)/2;
		// cout << mid <<nl;
		if (power(m, mid).arr[n-1][0] >= p) hi = mid;
		else lo = mid+1;
	}
    cout << lo << nl;
    return 0;
}
