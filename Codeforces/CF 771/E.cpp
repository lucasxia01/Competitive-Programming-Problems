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

const int MX = 1e6+100;

ll debt[MX];

struct seg {
    int l, r, c;
    bool operator<(const seg& o) const {
        return tie(l, r, c) < tie(o.l, o.r, o.c);
    }
};

set<seg> segs;

ll t[2*MX];
int n, q;

void modify(int l, int r, ll value) {
    l--;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) t[l++] += value;
    if (r&1) t[--r] += value;
  }
}

ll query(ll p) {
  ll res = 0;
  for (p += n; p > 0; p >>= 1) res += t[p];
  return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> q;
    segs.insert({1, n, 1});
    F0R(i, q) {
        string s; cin >> s;
        if (s == "Color") {
            int l, r, c; cin >> l >> r >> c;
            // erase a bunch of segs and add in 1 seg
            seg temp = {l+1, -INF, -1};
            auto it = segs.lower_bound(temp); it--;
            while (it != segs.end()) {
                if (it->r < l) { // no overlap
                    it++;
                } else if (it->l < l && it->r >= l && it->r <= r) { // some overlap
                    modify(l, it->r, debt[it->c]-debt[c]);
                    int L = it->l, C = it->c;
                    segs.insert({L, l-1, C});
                    auto it2 = it++;
                    segs.erase(it2);
                } else if (it->l >= l && it->r <= r) { // full overlap
                    modify(it->l, it->r, debt[it->c]-debt[c]);
                    auto it2 = it++;
                    segs.erase(it2);
                } else if (it->l >= l && it->l <= r && it->r > r) { // right overlap
                    modify(it->l, r, debt[it->c]-debt[c]);
                    int R = it->r, C = it->c;
                    segs.insert({r+1, R, C});
                    auto it2 = it++;
                    segs.erase(it2);
                } else if (it->l < l && it->r > r) { // contained
                    modify(l, r, debt[it->c]-debt[c]);
                    int L = it->l, R = it->r, C = it->c;
                    segs.insert({L, l-1, C});
                    segs.insert({r+1, R, C});
                    auto it2 = it++;
                    segs.erase(it2);
                } else { // no overlap
                    break;
                }
            }
            segs.insert({l, r, c});

            // trav(ss, segs) {
            //     cout << ss.l << " " << ss.r << " " << ss.c << endl;
            // } cout << endl;

        } else if (s == "Add") {
            int c; ll x; cin >> c >> x;
            debt[c] += x;
        } else {
            int i; 
            cin >> i;
            seg temp = {i+1, -INF, -1};
            auto it = segs.lower_bound(temp); it--;
            cout << debt[it->c] + query(i-1) << nl;
        }
    }
    
    return 0;
}
