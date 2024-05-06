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
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(...) dbg_out(__VA_ARGS__);
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){
	c << "(" << v.fi << "," <<v.se <<")"; return c;
}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){
	out << "{ ";
	trav(x,c) out<<x<<" ";
	out<<"}"; return out;
}
#else
#define dbg(...)
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1e6+5;

vi facs;

void gen_facs(vpi& pfs, int i, int x) {
    if (i == sz(pfs)) {
        facs.pb(x);
        return;
    }
    int cur = 1;
    F0R(j, pfs[i].s+1) {
        gen_facs(pfs, i+1, x*cur);
        cur *= pfs[i].f;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    vector<int> lp(MX);
    vector<int> pr;

    for (int i=2; i < MX; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] < MX; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        facs.clear();
        // factorizing n is hard
        int N = n;
        vpi pfs;
        while (n != 1) {
            int cnt = 0;
            int f = lp[n];
            while (n%f == 0) {
                n/=f;
                cnt++;
            }
            pfs.pb({f, cnt});
        }
        gen_facs(pfs, 0, 1);
        int c[N]; F0R(i, N) c[i] = -1;
        F0R(i, N) {
            bool vis[facs.size()+1];
            F0R(j, facs.size()+1) vis[j] = 0;
            trav(f, facs) {
                if (i-f < 0) continue;
                vis[c[i-f]] = 1;
            }
            F0R(j, facs.size()+1) {
                if (!vis[j]) {
                    c[i] = j;
                    break;
                }
            }
        }
        F0R(i, N) cout << (char)(c[i]+'a');
        cout << nl;
    }
    return 0;
}
