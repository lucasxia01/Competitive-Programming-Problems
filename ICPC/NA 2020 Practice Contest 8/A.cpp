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
vector<string> a[17];
void print() {
    F0R(i, 17) {
        trav(s, a[i]) cout << s << " ";
    }
    cout << nl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    string x;
    F0R(i, n) {
        cin >> x; 
        a[x.length()].pb(x);
    }
    FOR(i, 1, 16) {
        F0R(j, sz(a[i])) {
            // try both 1 and 9
            char temp = a[i][j][0];
            if (i == 1) a[i][j][0] = '0';
            else a[i][j][0] = '1';
            // dbg(a[i][j]);
            bool good = 0;
            F0R(k, j) {
                if (a[i][k] > a[i][j]) good = 1;
            }
            FOR(k, j+1, sz(a[i])-1) {
                if (a[i][k] < a[i][j]) good = 1;
            }
            if (good) {
                print();
                return 0;
            }
            a[i][j][0] = '9';
            // dbg(a[i][j]);
            F0R(k, j) {
                if (a[i][k] > a[i][j]) good = 1;
            }
            FOR(k, j+1, sz(a[i])-1) {
                if (a[i][k] < a[i][j]) good = 1;
            }
            if (good) {
                print();
                return 0;
            }
            a[i][j][0] = temp;
        }
    }
    cout << "impossible" << nl;
    return 0;
}