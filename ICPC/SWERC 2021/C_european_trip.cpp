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
const int N = 200;

template<class T, int N> struct Matrix {
	typedef Matrix M;
	array<array<T, N>, N> d{};
	M operator*(const M& m) const {
		M a;
		F0R(i,N) F0R(j,N)
			F0R(k,N) {
                a.d[i][j] += d[i][k]*m.d[k][j];
                a.d[i][j] %= MOD;
            }
		return a;
	}

	M operator^(ll p) const {
		M a, b(*this);
		F0R(i,N) a.d[i][i] = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b;
			p >>= 1;
		}
		return a;
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m, k; cin >> n >> m >> k;
    ll cnt[n]; memset(cnt, 0, sizeof cnt);
    ll gr[n][n]; F0R(i, n) F0R(j, n) gr[i][j] = 0;
    F0R(i, m) {
        int a, b; cin >> a >> b; a--; b--;
        cnt[a]++;
        cnt[b]++;
        gr[a][b] = gr[b][a] = 1;
    }
    if (k <= 2) { cout << 0 << nl; return 0; }
    Matrix<ll, N> a;
    F0R(i, n) F0R(j, n) a.d[i+n][j] = (i==j);
    F0R(i, n) F0R(j, n) a.d[i][j] = gr[i][j];
    // F0R(i, 200) {
    //     F0R(j, 100) cout << a.d[i][j] << " "; cout << nl;
    // }
    Matrix<ll, N> M;
    F0R(i, n) M.d[i+n][i] = 1;
    F0R(i, n) M.d[i][i+n] = -cnt[i]+MOD;
    F0R(i, n) F0R(j, n) M.d[i][j] = gr[i][j];
    a = M*a;
    F0R(i, n) M.d[i][i+n] =  (M.d[i][i+n]+1)%MOD;
    Matrix<ll, N> b = (M^(k-2))*a;

    ll ans = 0;
    F0R(i, n) ans = (ans + b.d[i][i])%MOD;
    cout << ans << nl;
    return 0;
}
