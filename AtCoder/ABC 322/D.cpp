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
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

vector<vpi > v[3];

void generate(int k, vpi &a) { // shifts
    FOR(i, -100, 100) {
        FOR(j, -100, 100) {
            vpi nxt;
            bool ok = 1;
            trav(x, a) {
                int nx = x.f+i, ny = x.s+j;
                if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) {
                    ok = 0;
                    break;
                }
                nxt.pb({nx, ny});
            }
            if (ok) v[k].pb(nxt);
        }
    }
}

vpi rotate(vpi a) {
    // 0, 0 goes to 0, 3
    // 0, 1 goes to 1, 3
    // i, j goes to j, 3-i
    vpi ret;
    trav(x, a) ret.pb({x.s, 3-x.f});
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    vpi a[3];
    
    int sum = 0;
    F0R(i, 3) {
        vpi tmp;
        F0R(j, 4) {
            string s; cin >> s;
            F0R(k, 4) if (s[k] == '#') tmp.pb({j, k});
        }
        a[i]= tmp;
        sum += sz(tmp);
        F0R(d, 4) {
            generate(i, a[i]);
            a[i] = rotate(a[i]);
        }
    }
    if (sum != 16) {
        cout << "No" << nl;
        return 0;
    }
    // now try putting them all together
    bool ok = 0;
    trav(v1, v[0]) {
        trav(v2, v[1]) {
            trav(v3, v[2]) {
                set<pi> s;
                trav(x, v1) {
                    s.insert(x);
                }
                trav(x, v2) {
                    s.insert(x);
                }
                trav(x, v3) {
                    s.insert(x);
                }
                if (sz(s) == 16) {
                    ok = 1;
                }
            }
        }
    }
    cout << (ok ? "Yes" : "No") << nl;
    return 0;
}
