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

const int MX = 505*505;
unordered_map<string, int> m;
int cnt = 0;
bool in[MX];

int get_val(string s) {
    if (m.find(s) == m.end()) {
        m[s] = cnt;
        cnt++;
    }
    return m[s];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;    
    vector<vector<int> > vO;
    vector<vector<int> > vA;
    F0R(i, n) {
        string s; cin >> s;
        if (s != "if") {
            in[get_val(s)] = 1;
        } else {
            bool o = 0, a = 0;
            vector<int> t;
            while (1) {
                cin >> s;
                if (s == "then") break;
                else if (s == "or") o = 1;
                else if (s == "and") a = 1;
                else t.pb(get_val(s));
            }
            cin >> s;
            t.pb(get_val(s));
            if (o) vO.pb(t);
            else vA.pb(t);
        }
    }
    bool change = 1;
    while (change) {
        change = 0;
        trav(v, vO) {
            if (in[v.back()]) continue;
            F0R(i, sz(v)-1) {
                if (in[v[i]]) {
                    in[v.back()] = 1;
                    change = 1;
                    break;
                }
            }
        }
        trav(v, vA) {
            bool ok = 1;
            if (in[v.back()]) continue;
            F0R(i, sz(v)-1) {
                if (!in[v[i]]) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                in[v.back()] = 1;
                change = 1;
            }
        }
    }
    int ans = 0;
    F0R(i, MX) ans+= (in[i]);
    cout << ans << nl;
    return 0;
}
