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

struct Trie {
    Trie* a[26] = {};
    int idx = -1;
};

int f[MX] = {};
void upd(int i, int x) {
    i++;
    while (i < MX) {
        f[i] += x;
        i += (i&-i);
    }
}
int query(int i) {
    i++;
    int sum = 0;
    while (i > 0) {
        sum += f[i];
        i -= (i&-i);
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    Trie root;
    vector<string> v;
    F0R(i, n) { string s; cin >> s; v.pb(s); }
    sort(all(v));
    F0R(i, n) {
        string s = v[i];
        Trie* cur = &root;
        F0R(i, s.length()) {
            if (cur->a[s[i]-'a'] == nullptr) cur->a[s[i]-'a'] = new Trie;
            cur = cur->a[s[i]-'a'];
        }
        cur->idx = i;
    }
    string s; cin >> s;
    int idx = 0;
    vi order;
    F0R(i, k) {
        Trie* cur = &root;
        while (1) {
            if (idx == s.length() || cur->a[s[idx]-'a'] == nullptr) break;
            else cur = cur->a[s[idx]-'a'];
            idx++;
        }
        order.pb(cur->idx);
    }
    ll ans = 0;
    F0R(i, k) upd(order[i], 1);
    reverse(all(order));
    ll cur = 1;
    idx = n-k+1;
    trav(o, order) {
        upd(o, -1);
//        dbg(o, o-query(o-1));
        ans = (((o-query(o-1))*cur)%MOD+ans)%MOD;
        cur = (cur*idx)%MOD;
        idx++;
    }
    ans = (ans+1)%MOD;
    cout << ans << nl;
    return 0;
}
