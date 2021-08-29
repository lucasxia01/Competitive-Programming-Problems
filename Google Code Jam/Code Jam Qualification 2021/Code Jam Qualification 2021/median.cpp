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

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t, n, q; cin >> t >> n >> q;
    while (t--) {
        if (n < 3) {
            F0R(i, n) cout << i+1 << " "; cout << nl;
            cout.flush();
            int x; cin >> x;
            if (x == -1) return 0;
            continue;
        }
        cout << "1 2 3" << nl;
        cout.flush();
        int x; cin >> x;
        vi v;
        if (x == 1) v = {2, 1, 3};
        else if (x == 2) v = {1, 2, 3};
        else v = {1, 3, 2};
        FOR(i, 4, n) {
            // ternary search for the position
            // there are i places to insert in
            // we want to split into i/3, i/3, i/3 first and so on
            int l = 0, r = sz(v);
            int pos = -1;
            while (l+1 < r) {
                int a = (2*l + r)/3, b = (l + 2*r)/3;
                if (a == b && b+1 < sz(v)) b++;
                else if (a == b) a--;
                assert(a >= 0 && b < sz(v));
                cout << v[a] << " " << v[b] << " " << i << nl;
                cout.flush();
                cin >> x;
                if (x == v[a]) {
                    r = a;
                    if (l >= r) pos = l;
                } else if (x == v[b]) {
                    l = b+1;
                    if (l >= r) pos = l;
                } else if (x == i){
                    l = a+1; r = b;
                    if (l > r) pos = l;
                    if (l == r) r++;
                    while (r >= sz(v)) { l--; r--; }
                    if (l < 0) { l++; r++;}
                } else return 0;
            }
            if (pos == -1) {
//                dbg(l, r, i);
                if (r >= sz(v)) {l--; r--; }
                cout << v[l] << " " << v[r] << " " << i << nl;
                cout.flush();
                cin >> x;
                if (x == v[l]) pos = l;
                else if (x == v[r]) pos = l+2;
                else if (x == i) pos = l+1;
                else return 0;
    //            dbg(i, l, r);
            }
//            dbg("inserting at", pos);
            v.insert(v.begin()+pos, i);
//            trav(u, v) cout << u << " "; cout << nl;
        }
        trav(u, v) cout << u << " "; cout << nl;
        cout.flush();
        cin >> x;
        if (x == -1) break;
    }
    
    return 0;
}
