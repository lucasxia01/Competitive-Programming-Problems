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
int freq[10] = {};

bool check() {
    int f[12] = {}; F0R(i, 10) f[i] = freq[i];
    // try greedily putting everything into straights of 3
    FOR(i, 1, 9) {
        while (f[i]) {
            if (f[i+1] && f[i+2]) {
                f[i+1]--;
                f[i+2]--;
            } else {
                return false;
            }
            f[i]--;
        }
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int x; cin >> x;
    vi v; F0R(i, 14) { int a; cin >> a; v.pb(a); }
    trav(u, v) freq[u]++;
    // now try replacing each one
    ld ans = 0;
    F0R(i, 14) {
        ld cur = 0;
        FOR(j, 1, 9) {
            // chance of getting this one is freq[j]
            ld p = ((ld)4-freq[j]);
            if (4-freq[j] == 0) continue;

            freq[v[i]]--;
            freq[j]++;
            bool ok = 0;
            // now with this multiset, try all possible pairs  and triples
            FOR(a, 1, 9) { // pair
                if (freq[a] < 2) continue; // we must have this
                freq[a]-=2;
                FOR(b, 1, 9) {
                    ok |= check();
                    if (freq[b] < 3) continue;
                    freq[b]-=3;
                    FOR(c, 1, 9) {
                        ok |= check();
                        if (freq[c] < 3) continue;
                        freq[c]-=3;
                        FOR(d, 1, 9) {
                            ok |= check();
                            if (freq[d] < 3) continue;
                            freq[d]-=3;
                            FOR(e, 1, 9) {
                                ok |= check();
                                if (freq[e] < 3) continue;
                                freq[e]-=3;
                                ok = 1;
                                freq[e]+=3;
                                
                            }
                            freq[d]+=3;
                        }
                        freq[c]+=3;
                    }
                    freq[b]+=3;
                }

                freq[a]+=2;
            }
            if (ok) {
                cur += p * (freq[x]+1);
            }

            freq[j]--;
            freq[v[i]]++;
        }
        ckmax(ans, cur/22);
    }
    cout.precision(10);
    cout << fixed << ans << nl;
    return 0;
}
