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

const int MX = 2000+35;
int sz[MX], p[MX];
int a[MX];

int n;

int find(int v) {
    return (v == p[v]?v:p[v]=find(p[v]));
}

void merge(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    if (b >= n) swap(a, b);
    // merge to the smaller dude
    if (a >= n && b >= n && a > b) swap(a, b);
    sz[a] += sz[b];
    p[b] = a;
}

void reset() {
    F0R(i, n) {
        sz[i] = 1;
        p[i] = i;
    }
    FOR(i, n, n+29) {
        sz[i] = 0;
        p[i] = i;
    }
    F0R(i, n) {
        F0R(k, 30) {
            if (a[i]&(1<<k)) merge(i, n+k);
        }
    }
}

bool check() {
    FOR(i, n, n+29) {
        if (find(i) == i && sz[i] == n) return 1;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        int ans = 0;
        F0R(i, n) {
            cin >> a[i];
            if (a[i] == 0) {
                ans++;
                a[i]++;
            }
        }
        reset();
        // check for everything being merged
        if (!check()) {
            ans++;
            bool done = 0;
            F0R(i, n) {
                a[i]--;
                reset();
                if (check()) {
                    done = 1;
                    break;
                }
                a[i]++;
                a[i]++;
                reset();
                if (check()) {
                    done = 1;
                    break;
                }
                a[i]--;
            }
            if (!done) { // now we have do TWO
                ans++;
                // find the largest minimum bit in comps
                reset();
                int pos = -1;
                FORd(i, n, n+29) {
                    if (find(i) == i && sz[i]) {
                        pos = i-n;
                        break;
                    }
                }
                F0R(i, n) {
                    if ((a[i]&(-a[i])) == (1<<pos)) {
                        a[i]--;
                        dbg(pos, i);
                        // now find the second position
                        F0R(j, n) {
                            if (i == j) continue;
                            if (find(j) == pos+n) {
                                a[j]++;
                                dbg("found j", j);
                                break;
                            }
                        }
                        reset();
                        if (check()) break;
                        break;
                    }
                }
            }
        }
        cout << ans << nl;
        F0R(i, n) cout << a[i] << " "; cout << nl;
    }
    return 0;
}
