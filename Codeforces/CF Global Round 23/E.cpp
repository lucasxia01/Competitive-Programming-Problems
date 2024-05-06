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

bool guess(int x) {
    cout << "! " << x << endl;
    cout.flush();
    string s; cin >> s;
    return (s == ":)");
}

bool query(vi u) {
    cout << "? "; cout << sz(u); trav(uu, u) cout << " " << uu;
    cout << endl;
    cout.flush();
    string s; cin >> s;
    return (s == "YES");
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    if (n == 1) {
        guess({1});
        return 0;
    }
    vi v; FOR(i, 1, n) v.pb(i);
    string s; 
    while (1) {
        int m = sz(v);
        vi sizes = {m/4, m/4, m/4, m/4};
        F0R(i, m%4) sizes[i]++;
        vi V[4];
        F0R(i, 4) {
            F0R(j, sizes[i]) {
                V[i].pb(v.back()); v.pop_back();
            }
        }
        vi u = V[0]; u.insert(u.end(), all(V[1]));
        bool b = query(u);
        u = V[0]; u.insert(u.end(), all(V[2]));
        bool c = query(u);
        
        int idx = b * 2 + c;
        v.clear();
        F0R(i, 4) {
            if (i != idx) v.insert(v.end(), all(V[i]));
        }
        // trav(vv, v) cout << vv << " "; cout << nl;
        if (v.size() == 2) {
            if(guess(v[0])) break;
            guess(v[1]);
            break;
        } else if (v.size() == 3) {
            u = {v[0], v[1]};
            vi w = {v[0]};
            b = query(u);
            if (!b) {
                if (guess(v[2])) break; 
                if (query(w)) guess(v[0]);
                else guess(v[1]);
            } else {
                if (!query(u)) {
                    if (guess(v[2])) break;
                    if (query(w)) guess(v[0]);
                    else guess(v[1]);
                } else {
                    if (guess(v[0])) break;
                    guess(v[1]);
                }
            }
            break;
        }
    }
    return 0;
}
