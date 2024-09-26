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
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 4e5+5;

struct SuffixArray {
    string s;
    int order[MX], eqClass[MX];
    vi lcp;
    SuffixArray(string t) {
        s = t;
        s += ' ';
        int n = (int) s.length();
        vector<pi> v;
        F0R(i, n) v.pb({s[i], i});
        sort(all(v));
        F0R(i, n) order[i] = v[i].s;
        eqClass[order[0]] = 0;
        FOR(i, 1, n-1) eqClass[order[i]] = eqClass[order[i-1]] + (v[i].f != v[i-1].f);
        int sz = 1;
        while (sz < n) {
            vector<pair<pi, int> > w;
            F0R(i, n) w.pb({{eqClass[(order[i]+n-sz)%n], eqClass[order[i]]}, (order[i]+n-sz)%n});
            count_sort(w);
            F0R(i, n) order[i] = w[i].s;
            eqClass[order[0]] = 0;
            FOR(i, 1, n-1) eqClass[order[i]] = eqClass[order[i-1]] + (w[i].f != w[i-1].f);
            sz *= 2;
        }
        
        int k = 0;
        F0R(i, n) lcp.pb(0);
        F0R(i, n-1) {
            int j = eqClass[i]; // rank of ith suffix
            int ii = order[j-1]; // index of suffix that comes before current suffix in ordering
            while (s[ii+k] == s[i+k]) k++;
            lcp[j] = k;
            k = max(k-1, 0);
        }
    }
    
    void count_sort(vector<pair<pi, int> >& w) {
        int n = sz(w);
        int c[n], p[n];
        F0R(i, n) c[i] = p[i] = 0;
        F0R(i, n) c[w[i].f.f]++;
        p[0] = 0;
        FOR(i, 1, n-1) p[i] = p[i-1] + c[i-1];
        vector<pair<pi, int> > w2 = w;
        F0R(i, n) w2[p[w[i].f.f]++] = w[i];
        w = w2;
    }
};

int SegTree[2*MX];
string s;
int len;
int query(int l, int r) {
    int ret = INF;
    for (l+=len, r+=len; l < r; l>>=1, r>>=1) {
        if (l&1) ckmin(ret, SegTree[l++]);
        if (r&1) ckmin(ret, SegTree[--r]);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> s;
    len = (int) s.length();
    SuffixArray sa(s);
//    F0R(i, len+1) cout << sa.order[i] << " "; cout << nl;
//    F0R(i, len+1) cout << sa.lcp[i] << " "; cout << nl;
//    F0R(i, len+1) cout << sa.eqClass[i] << " "; cout << nl;
    F0R(i, len) SegTree[i+len] = sa.lcp[i+1];
    F0Rd(i, len) SegTree[i] = min(SegTree[i<<1], SegTree[i<<1|1]);
    int n; cin >> n;
    vector<pair<pi, pi > > v;
    F0R(i, n) {
        int l, r; cin >> l >> r;
        int rank = sa.eqClass[l-1];
        int lo = 0, hi = rank;
        while (lo < hi) {
            int mid = (lo+hi)/2;
            if (query(mid, rank) < r-l+1) lo = mid+1;
            else hi = mid;
        }
//        dbg(rank, s.substr(l-1, r-l+1), lo);
        v.pb({{lo, r-l}, {l, r}});
    }
    sort(all(v));
    trav(u, v) cout << u.s.f << " " << u.s.s << nl;
    return 0;
}
