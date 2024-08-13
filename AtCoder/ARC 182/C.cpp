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
const ll mod = 998244353;
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

/**** Credit to chatgpt 4.0 ****/

// Stream operator for std::pair
template<typename T1, typename T2>
ostream& operator<<(ostream &out, const pair<T1, T2> &v) {
    out << "(" << v.first << ", " << v.second << ")"; 
    return out;
}

// Trait to check if a type is iterable
template<typename T, typename = void>
struct is_iterable : false_type {};

template<typename T>
struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type {};

// Stream operator for iterable types excluding std::string
template<typename TT>
typename enable_if<is_iterable<TT>::value && !is_same<TT, string>::value, ostream&>::type
operator<<(ostream& out, const TT& c) {
    out << "{ ";
    for (const auto& x : c) out << x << " ";
    out << "}"; 
    return out;
}

template<typename T>
ostream& operator<<(ostream& out, std::stack<T> container) {
    std::vector<T> elements;
    while (!container.empty()) {
        elements.push_back(container.top());
        container.pop();
    }
    std::reverse(elements.begin(), elements.end()); // Reverse to maintain order
    return out << elements;
}

template<typename T>
ostream& operator<<(ostream& out, std::queue<T> container) {
    std::vector<T> elements;
    while (!container.empty()) {
        elements.push_back(container.front());
        container.pop();
    }
    return out << elements;
}

// Helper function to print std::priority_queue
template<typename T, typename Container, typename Compare>
ostream& operator<<(ostream& out, std::priority_queue<T, Container, Compare> pq) {
    out << "{";
    while (!pq.empty()) {
        out << " " << pq.top();
        pq.pop();
    }
    out << " }";
    return out;
}

#ifdef DBG
void dbg_out() { cerr << endl; }

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}

#define dbg(...) cerr << #__VA_ARGS__ << ":", dbg_out(__VA_ARGS__);
#define dbg_array(a, n) cerr << #a << ": { "; for(int i = 0; i < n; i++) cerr << a[i] << " "; cerr << "}\n";
#else
#define dbg(...)
#define dbg_array(a, n)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

template<class T, int N> struct Matrix {
	typedef Matrix M;
	array<array<T, N>, N> d{};
    M operator-(const M& m) const {
        M a;
        rep(i,0,N) rep(j,0,N)
            a.d[i][j] = ((d[i][j] - m.d[i][j])%mod+mod)%mod;
        return a;
    }
    M operator+(const M& m) const {
        M a;
        rep(i,0,N) rep(j,0,N)
            a.d[i][j] = (d[i][j] + m.d[i][j])%mod;
        return a;
    }
	M operator*(const M& m) const {
		M a;
		rep(i,0,N) rep(j,0,N)
			rep(k,0,N) {
                a.d[i][j] += (d[i][k]*m.d[k][j])%mod;
                a.d[i][j] %= mod;
            }
		return a;
	}
	vector<T> operator*(const vector<T>& vec) const {
		vector<T> ret(N);
		rep(i,0,N) rep(j,0,N) {
            ret[i] += (d[i][j] * vec[j])%mod;
            ret[i] %= mod;
        }
		return ret;
	}
	M operator^(ll p) const {
		assert(p >= 0);
		M a, b(*this);
		rep(i,0,N) a.d[i][i] = 1;
		while (p) {
			if (p&1) a = a*b;
			b = b*b;
			p >>= 1;
		}
		return a;
	}
};

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

template <int N>
int matInv(array<array<ll, N>, N>& A) {
	int n = sz(A); vi col(n);
	vector<vector<ll>> tmp(n, vector<ll>(n));
	rep(i,0,n) tmp[i][i] = 1, col[i] = i;

	rep(i,0,n) {
		int r = i, c = i;
		rep(j,i,n) rep(k,i,n) if (A[j][k]) {
			r = j; c = k; goto found;
		}
		return i;
found:
		A[i].swap(A[r]); tmp[i].swap(tmp[r]);
		rep(j,0,n)
			swap(A[j][i], A[j][c]), swap(tmp[j][i], tmp[j][c]);
		swap(col[i], col[c]);
		ll v = modpow(A[i][i], mod - 2);
		rep(j,i+1,n) {
			ll f = A[j][i] * v % mod;
			A[j][i] = 0;
			rep(k,i+1,n) A[j][k] = (A[j][k] - f*A[i][k]) % mod;
			rep(k,0,n) tmp[j][k] = (tmp[j][k] - f*tmp[i][k]) % mod;
		}
		rep(j,i+1,n) A[i][j] = A[i][j] * v % mod;
		rep(j,0,n) tmp[i][j] = tmp[i][j] * v % mod;
		A[i][i] = 1;
	}

	for (int i = n-1; i > 0; --i) rep(j,0,i) {
		ll v = A[j][i];
		rep(k,0,n) tmp[j][k] = (tmp[j][k] - v*tmp[i][k]) % mod;
	}

	rep(i,0,n) rep(j,0,n)
		A[col[i]][col[j]] = tmp[i][j] % mod + (tmp[i][j] < 0)*mod;
	return n;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll n; int m; cin >> n >> m;
    if (m == 1) {
        cout << n%mod << nl;
        return 0;
    }
    // create the matrix for m
    const int len = 6;
    vi primes = {2, 3, 5, 7, 11, 13};
    vi cnts[m+1];
    FOR(i, 1, m) {
        int j = i;
        F0R(k, 6) {
            int cnt = 0;
            while (j%primes[k] == 0) {
                j /= primes[k];
                cnt++;
            }
            cnts[i].pb(cnt);
        }
        dbg(i, cnts[i]);
    }
    // create matrix M
    const int l = (1<<len);
    Matrix<int, l> M;
    FOR(v, 1, m) {
        int curmask = 0;
        F0R(k, 6) if (cnts[v][k]) curmask |= (1<<k);
        F0R(i, l) {
            int submask = i;
            for (; submask > 0; submask = (submask-1)&i) {
                int newmask = (i^submask);
                if ((newmask&curmask) == newmask) {
                    ll prod = 1;
                    F0R(k, 6) {
                        if (newmask&(1<<k))
                            prod = (prod * cnts[v][k]) % mod;
                    }
                    dbg(i, submask, prod);
                    M.d[i][submask] += prod;
                    M.d[i][submask] %= mod;
                }
            }
            // handle submask of 0
            submask = 0;
            int newmask = (i^submask);
            if ((newmask&curmask) == newmask) {
                ll prod = 1;
                F0R(k, 6) {
                    if (newmask&(1<<k))
                        prod = (prod * cnts[v][k]) % mod;
                }
                dbg(i, submask, prod);
                M.d[i][submask] += prod;
                M.d[i][submask] %= mod;
            }
        }
    }
    // F0R(i, l) {
    //     dbg(M.d[i]);
    // }

    Matrix<int, l> denom = M;
    Matrix<int, l> iden; F0R(i, l) iden.d[i][i] = 1;
    denom = M-iden;
    int rank = matInv<l>(denom.d);
    assert(rank == l);
    dbg(rank);
    Matrix<int, l> result = (((M^((n+1)%(mod-1))) - iden) * denom) - iden;
    vi vec(l, 0); vec[0] = 1;
    auto v = result * vec;
    // get sum of v I guess
    ll ans = 0;
    F0R(i, l) ans = (ans + v[i])%mod;
    cout << ans << endl;
    return 0;
}
