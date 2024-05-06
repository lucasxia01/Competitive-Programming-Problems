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

const int MX = 3e5+5;

struct Node {
    Node* c[2];
    Node* get_child(bool i) {
        if (!c[i]) c[i] = new Node();
        return c[i];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int a[n]; F0R(i, n) cin >> a[i];
    vpi v; F0R(i, n) v.pb({a[i], i});
    sort(all(v));
    Node* root = new Node();
    Node* p[31][n]; F0R(i, n) p[30][i] = root;
    int ans[n]; F0R(i, n) ans[i] = 0;
    F0Rd(j, 30) {
        bool ok = 1;
        // advance them until no groups of 3 left
        F0R(i, n) {
            p[j][i] = p[j+1][i]->get_child(v[i].f&(1<<j));
        }
        F0R(i, n) {
            int ii = i+1;
            while (ii < n && p[j][ii] == p[j][i]) ii++;
            if (ii-i > 2) ok = 0;
            i = ii-1;
        }
        F0R(i, n) {
            dbg(v[i].f, p[j][i]);
        }
        dbg(j, ok);
        if (ok) {
            // split up the 4s as best as possible in p[j+1]
            F0R(i, n) {
                int ii = i+1;
                while (ii < n && p[j+1][ii] == p[j+1][i]) ii++;
                assert(ii-i <= 4);
                // either 010 or 011 for 3
                // either 0101, 0110 for 4
                if (ii-i == 3) {
                    // find the split
                    ans[v[i].s] = 0;
                    if ((v[i+1].f^v[i].f) >= (v[i+2].f^v[i].f) &&
                        (v[i+1].f^v[i].f) >= (v[i+1].f^v[i+2].f)) {
                        ans[v[i+1].s] = 0;
                        ans[v[i+2].s] = 1;
                    } else if ((v[i+2].f^v[i].f) >= (v[i+1].f^v[i+2].f)) {
                        ans[v[i+1].s] = 1;
                        ans[v[i+2].s] = 0;
                    } else {
                        ans[v[i+1].s] = 1;
                        ans[v[i+2].s] = 1;
                    }
                } else if (ii-i == 4) {
                    ans[v[i].s] = 0;
                    ans[v[i+1].s] = 1;
                    if (min((v[i].f^v[i+2].f), (v[i+1].f^v[i+3].f)) >= min((v[i].f^v[i+3].f), (v[i+1].f^v[i+2].f))) {
                        ans[v[i+2].s] = 0;
                        ans[v[i+3].s] = 1;
                    } else {
                        ans[v[i+2].s] = 1;
                        ans[v[i+3].s] = 0;
                    }
                } else if (ii-i == 2) {
                    ans[v[i].s] = 0;
                    ans[v[i+1].s] = 1;
                }
                i = ii-1;
            }
            break;
        }
    }
    F0R(i, n) cout << ans[i];
    cout << nl;
    return 0;
}
