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

#define int long long

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
// const ll INF = (1<<29) + 123;
const ll MOD = 1e9+7; // 998244353
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

const int MX = 100+5;
unordered_map<string, int> m;
int cnt = 0;

ll get_val(string s) {
    if (m.find(s) == m.end()) {
        m[s] = cnt;
        cnt++;
    }
    return m[s];
}

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a)%MOD;
        a = (a * a)%MOD;
        b >>= 1;
    }
    return res;
}

vector<vector<ll> > mat;

bool gauss (vector<vector<ll> > a) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (a[i][col] != 0)
                sel = i;
        if (a[sel][col] == 0)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        for (int i=0; i<n; ++i)
            if (i != row) {
                ll c = (a[i][col]*binpow(a[row][col], MOD-2))%MOD;
                for (int j=col; j<=m; ++j)
                    a[i][j] = ((a[i][j]-(a[row][j] * c)%MOD)%MOD+MOD)%MOD;
            }
        ++row;
    }

    
    // check if there is row of only 1 nonzero
    F0R(i, n) {
        int c = 0;
        F0R(j, cnt) {
            if (a[i][j] != 0) c++;
            // cout << a[i][j] << " ";
        }
        if (c == 1) return 0;
        // cout << nl;
    }
    return 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    string line;
    getline(cin, line);
    F0R(i, n) {
        vector<ll> v(MX, 0);
        getline(cin, line);
        line += ' ';
        string t = "";
        int mul = 1, eq = 1;
        trav(c, line) {
            if (c == ' ') {
                if (t == "") continue;
                v[get_val(t)] = ((v[get_val(t)]+mul*eq)%MOD+MOD)%MOD;
                t = "";
            } else if (c == '=') {
                eq = -1;
                mul = 1;
            } else if (c == '*') {
                mul = 1;
            } else if (c == '/') {
                mul = -1;
            } else if (c == '1') {
                continue;
            } else {
                t += c;
            }
        }
        mat.pb(v);
    }
    // F0R(i, n) {
    //     F0R(j, cnt) cout << mat[i][j] << " ";
    //     cout << nl;
    // } cout << nl;
    if (gauss(mat)) cout << "valid" << nl;
    else cout << "invalid" << nl;

    return 0;
}
